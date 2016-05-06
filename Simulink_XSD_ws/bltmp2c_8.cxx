#include "bltmp2c.hxx"

// #define DELETE_FALSE_EDGE 1

void bltmp_8_output(void) {
    blclst_T *blclst = hier[0].clst;
    int clst_n = hier[0].clst_n;
    ofstream ofs("tmp_results.csv");

    for(int i=0; i<clst_n; i++) {
	ofs << blclst[i].u.bl.org->p_block->name() << ",,"
	    << blclst[i].core << endl;

        stringstream s;
        s << blclst[i].core;
	blclst[i].u.bl.org->p_block->peinfo(s.str());
//	cout << blclst[i].u.bl.org->p_block->name() << "-> core "
//	    << blclst[i].u.bl.org->p_block->peinfo()  << endl;
    }
    ofs.close();

#ifdef __BLG_WITH_GRAPHVIZ__
#ifdef DELETE_FALSE_EDGE
    blconn_T *blconn = hier[0].conn;
    int conn_n = hier[0].conn_n;

    for(int i=0; i<conn_n; i++) {
	if(blconn[i].flag == FALSE) bltmp_delete_bledge(i);
    }
#endif
    p_graph->dumpDotFile("_blgraph.dot");
#endif

    xml_schema::namespace_infomap map;
    map["SM"].name   = "http://example.com/SimulinkModel";
    map["SM"].schema = "SimulinkModel.xsd";
    blocks_T xml = xrd.xml_blocks();
    ofs.open(outfile);
    blocks(ofs, xml, map);
    ofs.close();
}
