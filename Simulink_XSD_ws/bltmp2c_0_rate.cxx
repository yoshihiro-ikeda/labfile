#include "bltmp2c.hxx"

static void bltmp_0_4_1_period_to_rate(blclst_T *, int);
static void bltmp_0_4_2_subsystem_to_block(blclst_T *, int);
static int bltmp_0_4_3_forward_process(blclst_T *, int, int);
static int bltmp_0_4_4_backward_process(blclst_T *, int, int);
static void bltmp_0_4_5_propagate_from_trigger(blclst_T *, int);
static void bltmp_0sub_prop_subsystem(blclst_T *, stringstream *);
static void bltmp_0_4_6_prop_inter_port(blclst_T *, int);
static void bltmp_0_4_7_block_to_subsystem(blclst_T *, int);
static void bltmp_0sub_rate_prop_node_forward(blclst_T *, blclst_T *, blclst_T **, int);
static void bltmp_0sub_rate_prop_node_backward(blclst_T *, blclst_T *, blclst_T **, int);
static blclst_T *bltmp_0sub_get_finer_rate(blclst_T *, blclst_T *);
static float bltmp_0sub_rate_num(blclst_T *);
static void bltmp_0_4_9_rate_propagation_check(blclst_T *, int);

void bltmp_0_4_rate_propagation(void) {
    blclst_T *blclst = hier[0].clst;
    int clst_n = hier[0].clst_n;

    bltmp_0_4_1_period_to_rate(blclst, clst_n);
    bltmp_0_4_2_subsystem_to_block(blclst, clst_n);

    // main loop
    int kk=-1, kk_old, PHASE=0;
    while(TRUE) {
	kk_old = kk;
	kk = bltmp_0_4_3_forward_process(blclst, clst_n, PHASE);
	bltmp_0_4_5_propagate_from_trigger(blclst, clst_n);
	if(kk == 0) break;
	kk = bltmp_0_4_4_backward_process(blclst, clst_n, PHASE);
	if(kk == 0) break;
	if(kk == kk_old) {
	    if(PHASE < 2) {
		PHASE++;
	    } else {
		break;
	    }
	} else {
	    if(PHASE < 2) continue;
	}
	bltmp_0_4_6_prop_inter_port(blclst, clst_n);
    }
    bltmp_0_4_7_block_to_subsystem(blclst, clst_n);
    bltmp_0_4_9_rate_propagation_check(blclst, clst_n);
}

static void bltmp_0_4_1_period_to_rate(blclst_T *blclst, int clst_n) {
    blclst_T *node;

    for(int i=0; i<clst_n; i++) {
	node = &(blclst[i]);
	node->u.bl.alike.rate = &(node->u.bl.org->p_block->rate());
	if(node->u.bl.org->p_block->Period()) {
            stringstream s;
	    s << *(node->u.bl.org->p_block->Period());
cerr << "period " << s.str() << endl;
	    node->u.bl.org->p_block->rate(s.str());
	}
    }
}

// If subsysytem has rate, just propagete. Do we need to process from top hierarchy of subsystems?
static void bltmp_0_4_2_subsystem_to_block(blclst_T *blclst, int clst_n) {
    blclst_T *node, *child;

    for(int i=0; i<clst_n; i++) {
	node = &(blclst[i]);
	if(bltmp_is_subsystem(node)) {
	    if(bltmp_has_effective_rate(node)) {
		for(child=node->u.bl.ss_child; child; 
			child=child->u.bl.ss_sibling) {
		   if(bltmp_has_effective_rate(child)) {
			// if(**node->u.bl.alike.rate != **child->u.bl.alike.rate)
			    // cerr << "Warning: Different rate subsystem "
			    // << node->u.bl.org->p_block->name() << " (" 
			    // << **node->u.bl.alike.rate << ") and its child "
			    // << child->u.bl.org->p_block->name() << " (" 
			    // << **child->u.bl.alike.rate << ")" << endl;
		   } else {
			*child->u.bl.alike.rate = *node->u.bl.alike.rate;
		   }
		}
	    }
	}
    }
}

static int bltmp_0_4_3_forward_process(blclst_T *blclst, int clst_n, int phase) {
    blclst_T *Q = NULL, *node;
    int kk = 0;

    for(int i=0; i<clst_n; i++) {
	node = &blclst[i];
	if(bltmp_has_effective_rate(node)) {
	    node->Qnext = Q;
	    Q = node;
	    node->tmp = TRUE;	// on Queue
// cout << "Add0: node " << node->pos << ":" << bltmp_get_name(node) << endl;
	} else {
	    node->tmp = FALSE;	// off Queue
	    if(!bltmp_is_subsystem(node)) kk++;
	}
    }
    if(kk == 0) return kk;
cerr << "PHASE " << phase << ": before forward: " << kk << endl;
    while(Q) {
	node = Q;
	Q = Q->Qnext;
	node->tmp = FALSE;
// cout << "Del node " << node->pos << ":" << bltmp_get_name(node) << endl;
	bltmp_0sub_rate_prop_node_forward(blclst, node, &Q, phase);
    }
    return kk;
}

static int bltmp_0_4_4_backward_process(blclst_T *blclst, int clst_n, int phase) {
    blclst_T *Q = NULL, *node;
    int kk = 0;

    for(int i=0; i<clst_n; i++) {
	node = &blclst[i];
	if(bltmp_has_effective_rate(node)) {
	    node->Qnext = Q;
	    Q = node;
	    node->tmp = TRUE;	// on Queue
// cout << "Add0: node " << node->pos << ":" << bltmp_get_name(node) << endl;
	} else {
	    node->tmp = FALSE;	// off Queue
	    if(!bltmp_is_subsystem(node)) kk++;
	}
    }
    if(kk == 0) return kk;
cerr << "PHASE " << phase << ": before backward: " << kk << endl;
    while(Q) {
	node = Q;
	Q = Q->Qnext;
	node->tmp = FALSE;
// cout << "Del node " << node->pos << ":" << bltmp_get_name(node) << endl;
	bltmp_0sub_rate_prop_node_backward(blclst, node, &Q, phase);
    }
    return kk;
}

static void bltmp_0_4_5_propagate_from_trigger(blclst_T *blclst, int clst_n) {
    blclst_T *node, *nd;
    blconn_T *conn;

    for(int i=0; i<clst_n; i++) {
	node = &(blclst[i]);
	if((bltmp_get_blocktype(node) != "TriggerPort") &&
	    (bltmp_get_blocktype(node) != "ActionPort")) continue;
// cout << "Check Special Port: " << bltmp_get_name(node) << endl;
	for(conn=node->conn_t; conn; conn=conn->next_t) {
	    nd = &blclst[conn->pos_s];
// cout << "--- Check node: " << bltmp_get_name(nd) << ": rate=" << *bltmp_get_rate(nd) << endl;
	    if(bltmp_has_effective_rate(nd)) break;
	}
// cout << "conn: " << conn << endl;
	if(conn) {
	    float x = std::atof((**bltmp_get_rate(nd)).c_str());
            stringstream s;
	    s << x/2.0;
// cout << "Find Special Port: " << bltmp_get_name(node) << ": rate=" << **bltmp_get_rate(nd) << endl;
	    bltmp_0sub_prop_subsystem(node->u.bl.ss_parent, &s);
	}
    }
}

static void bltmp_0sub_prop_subsystem(blclst_T *sub, stringstream *s) {
    blclst_T *node;

// cout << "Write to SubSystem: " << bltmp_get_name(sub) << ": rate=" << s->str() << endl;
    for(node=sub->u.bl.ss_child; node; node=node->u.bl.ss_sibling) {
	if(bltmp_is_specialport(node)) continue;
	if(bltmp_is_subsystem(node)) bltmp_0sub_prop_subsystem(node, s);
	node->u.bl.org->p_block->rate(s->str());
    }
}

static void bltmp_0_4_6_prop_inter_port(blclst_T *blclst, int clst_n) {
    blclst_T *node, *node2, *nd;

    for(int i=0; i<clst_n; i++) {
	node = &(blclst[i]);
	if(!bltmp_is_subsystem(node)) continue;
// cout << "H node(subsystem) " << node->u.bl.org->p_block->name() << endl;
	node2 = NULL;
	for(nd=node->u.bl.ss_child; nd; nd=nd->u.bl.ss_sibling) {
// cout << "H nd(subsystem) " << nd->u.bl.org->p_block->name() << endl;
	    if(!bltmp_is_ioport(nd)) continue;
	    if(!bltmp_has_effective_rate(nd)) continue;
	    if(!node2) node2 = nd;
	    else node2 = bltmp_0sub_get_finer_rate(node2, nd);
	}
	if(!node2) continue;
// cout << "H node2(rate) " << node2->u.bl.org->p_block->name() << endl;
	for(nd=node->u.bl.ss_child; nd; nd=nd->u.bl.ss_sibling) {
	    if(!bltmp_is_ioport(nd)) continue;
	    if(bltmp_has_effective_rate(nd)) continue;
	    nd->u.bl.org->p_block->rate(*node2->u.bl.alike.rate);
// cout << "H copy " << **nd->u.bl.alike.rate << " to " << nd->u.bl.org->p_block->name() << endl;;
	}
    }
}

// copy rate values to subsystem blocks
static void bltmp_0_4_7_block_to_subsystem(blclst_T *blclst, int clst_n) {
    blclst_T *node, *child;

    for(int i=0; i<clst_n; i++) {
	node = &(blclst[i]);
	if(bltmp_is_subsystem(node)) {
	    if(bltmp_has_effective_rate(node)) continue;
	    for(child=node->u.bl.ss_child; child; 
			child=child->u.bl.ss_sibling) {
		if(!bltmp_has_effective_rate(child)) continue;
		node->u.bl.org->p_block->rate(*child->u.bl.alike.rate);
// cout << "copy rate node " << child->pos << " to " << node->pos 
// << ": value " << *child->u.bl.alike.rate << endl;
		break;
	    }
	}
    }
}

static void bltmp_0sub_rate_prop_node_forward(blclst_T *blclst, blclst_T *node, blclst_T **Q, int phase) {
    blclst_T *node2, *nd;
    blconn_T *conn, *conn2;
    int mult_flag;

    // check all outputs of node
    for(conn=node->conn_s; conn; conn=conn->next_s) {
// cout << "process conn " << conn->pos_s << "," << conn->pos_t << endl;
	node2 = &blclst[conn->pos_t];
// cout << "check: node " << node2->pos << ":" << node2->u.bl.org->p_block->name() << endl;
	// node2 has rate already
	if(bltmp_has_effective_rate(node2)) {
	    // Need to check multiple rate?
	    continue;
	}
	// when node2 is simple block
	if(bltmp_single_rate_terminals(node2)) {
	    if((*node2->u.bl.alike.rate) && 
		(**(node2->u.bl.alike.rate) == **(node->u.bl.alike.rate))) continue;
	    node2->u.bl.org->p_block->rate(*node->u.bl.alike.rate);
	    if(node2->tmp == FALSE) {
		node2->Qnext = *Q;
		*Q = node2;
		node2->tmp = TRUE;
// cout << "add1: node " << node2->pos << ":" << **node2->u.bl.alike.rate << ":" << node2->u.bl.org->p_block->name() << endl;
	    }
	    continue;
	}
	// muiti-rate terminal block: check all inputs of node2
	mult_flag = FALSE;
	for(conn2=node2->conn_t; conn2; conn2=conn2->next_t) {
	    nd = &blclst[conn2->pos_s];
	    if(nd == node) continue;
	    if(phase < 2)
	        if(!bltmp_has_effective_rate(nd)) break;
	    if(**(nd->u.bl.alike.rate) == **(node->u.bl.alike.rate)) continue;
	    mult_flag = TRUE;
	}
	// when all neighbor nodes connecting inputs of node2
	if((phase >= 2) || (!conn2)) {
	    if(mult_flag == FALSE) {
	        if((*node2->u.bl.alike.rate) && 
		    (**(node2->u.bl.alike.rate) == **(node->u.bl.alike.rate))) continue;
		node2->u.bl.org->p_block->rate(*node->u.bl.alike.rate);
	    } else { // need to set G.C.D.
		// cerr << "Multiple Rates: " 
		//     << node2->u.bl.org->p_block->name() << ", type: " 
		//     << node2->u.bl.org->p_block->blocktype() << endl;
		blconn_T *cn = node2->conn_t;
		blclst_T *nodex = &blclst[cn->pos_s];
		for(cn=cn->next_t; cn; cn=cn->next_t) {
		    blclst_T *nd2 = &blclst[cn->pos_s];
		    nodex = bltmp_0sub_get_finer_rate(nodex, nd2);
		    // if(!(*nd2->u.bl.alike.rate)) cerr << "--- NIL (";
		    // else cerr << "--- " << **(nd2->u.bl.alike.rate) << " (";
		    // cerr << nd2->u.bl.org->p_block->name() << ")" << endl;
		}
	        if((*node2->u.bl.alike.rate) && 
		    (**(node2->u.bl.alike.rate) == **(nodex->u.bl.alike.rate))) {
		    // cerr << "no change" << endl;
		    continue;
		}
		node2->u.bl.org->p_block->rate(*nodex->u.bl.alike.rate);
		// cerr << "take " << **(nodex->u.bl.alike.rate) << endl;
	    }
	    if(node2->tmp == FALSE) {
		node2->Qnext = *Q;
		*Q = node2;
		node2->tmp = TRUE;
// cout << "add2: node " << node2->pos << ":" << **node2->u.bl.alike.rate << ":" << node2->u.bl.org->p_block->name() << endl;
	    }
	}
    }
}

static void bltmp_0sub_rate_prop_node_backward(blclst_T *blclst, blclst_T *node, blclst_T **Q, int phase) {
    blclst_T *node2, *nd;
    blconn_T *conn, *conn2;
    int mult_flag;

    // check all inputs of node
    for(conn=node->conn_t; conn; conn=conn->next_t) {
	node2 = &blclst[conn->pos_s];
// cout << "check: node2 " << node2->pos << ":" << node2->u.bl.org->p_block->name() << endl;
	// node2 has rate already
	if((*node2->u.bl.alike.rate) && (**(node2->u.bl.alike.rate) != "-1")
	    && (**(node2->u.bl.alike.rate) != "0")
	    && (**(node2->u.bl.alike.rate) != "inf")) {  // No "SampleTime" for backward propagation
	    // Need to check multiple rate?
	    continue;
	}
	// when node2 is simple block
	if(bltmp_single_rate_terminals(node2)) {
	    if((*node2->u.bl.alike.rate) && 
		(**(node2->u.bl.alike.rate) == **(node->u.bl.alike.rate))) continue;
	    node2->u.bl.org->p_block->rate(*node->u.bl.alike.rate);
	    if(node2->tmp == FALSE) {
		node2->Qnext = *Q;
		*Q = node2;
		node2->tmp = TRUE;
// cout << "add1: node " << node2->pos << ":" << **node2->u.bl.alike.rate << ":" << node2->u.bl.org->p_block->name() << endl;
	    }
	    continue;
	}
	// multi-rate terminal block: check all outputs of node2
	mult_flag = FALSE;
	for(conn2=node2->conn_s; conn2; conn2=conn2->next_s) {
	    nd = &blclst[conn2->pos_t];
// cout << "check: output node " << nd->pos << ":" << nd->u.bl.org->p_block->name() << endl;
	    if(nd == node) continue;
	    if(phase < 2)
	      if(!bltmp_has_effective_rate(nd)) break;
	    if(**(nd->u.bl.alike.rate) == **(node->u.bl.alike.rate)) continue;
	    mult_flag = TRUE;
	}
	// when all neighbor nodes connecting outputs of node2
	if((phase = 2) || (!conn2)) {
	    if(mult_flag == FALSE) {
	        if((*node2->u.bl.alike.rate) && 
		    (**(node2->u.bl.alike.rate) == **(node->u.bl.alike.rate))) continue;
		node2->u.bl.org->p_block->rate(*node->u.bl.alike.rate);
	    } else { // need to set G.C.D.
		// cerr << "Multiple Rates: " 
		//     << node2->u.bl.org->p_block->name() << ", type: " 
		//     << node2->u.bl.org->p_block->blocktype() << endl;
		blconn_T *cn = node2->conn_s;
		blclst_T *nodex = &blclst[cn->pos_t];
		for(cn=cn->next_s; cn; cn=cn->next_s) {
		    blclst_T *nd2 = &blclst[cn->pos_t];
		    nodex = bltmp_0sub_get_finer_rate(nodex, nd2);
		    // if(!(*nd2->u.bl.alike.rate)) cerr << "--- NIL (";
		    // else cerr << "--- " << **(nd2->u.bl.alike.rate) << " (";
		    // cerr << nd2->u.bl.org->p_block->name() << ")" << endl;
		}
	        if((*node2->u.bl.alike.rate) && 
		    (**(node2->u.bl.alike.rate) == **(nodex->u.bl.alike.rate))) {
		    // cerr << "no change" << endl;
		    continue;
		}
		node2->u.bl.org->p_block->rate(*nodex->u.bl.alike.rate);
		// cerr << "take " << **(nodex->u.bl.alike.rate) << endl;
	    }
	    if(node2->tmp == FALSE) {
		node2->Qnext = *Q;
		*Q = node2;
		node2->tmp = TRUE;
// cout << "add2: node " << node2->pos << ":" << **node2->u.bl.alike.rate << ":" << node2->u.bl.org->p_block->name() << endl;
	    }
	}
    }
}

static blclst_T *bltmp_0sub_get_finer_rate(blclst_T *node1, blclst_T *node2) {
    float x1 = bltmp_0sub_rate_num(node1);
    float x2 = bltmp_0sub_rate_num(node2);
    return (x1 < x2) ? node1 : node2;
}

static float bltmp_0sub_rate_num(blclst_T *node) {
    float x;
    if(**bltmp_get_rate(node) == "SampleTime") return 4.0;
    if(**bltmp_get_rate(node) == "-1") return 3.0;
    if(**bltmp_get_rate(node) == "0") return 2.5;
    if(**bltmp_get_rate(node) == "inf") return 2.0;
    x = std::atof((**bltmp_get_rate(node)).c_str());
    if(x == 0) x = 0.5;		// temporary
    return x;
}

static void bltmp_0_4_9_rate_propagation_check(blclst_T *blclst, int clst_n) {
    for(int i=0; i<clst_n; i++) {
	blclst_T *node = &(blclst[i]);
	if(bltmp_has_effective_rate(node)) continue;
	cerr << "Rate(?):";
	if(!(*bltmp_get_rate(node))) cerr << "--- NIL (";
	else cerr << "--- " << **bltmp_get_rate(node) << " (";
	cerr << bltmp_get_name(node) << ")" << endl;
    }
}
