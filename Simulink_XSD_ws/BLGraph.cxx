// BL Graphのインプリメンテーションファイル
#include "BLGraph.hxx"

#include <iostream>
#include <fstream>
#include <memory>
// #include <sstream>

#include <algorithm>

#include <xercesc/dom/DOM.hpp>


#ifndef __DEBUG_MESSAGE__
//#define __DEBUG_MESSAGE__
#endif

#ifdef __BLG_WITH_GRAPHVIZ__
#include <graphviz/types.h>
#endif

namespace BLG{
  // Constructor
  BLGraph::BLGraph
  (
   ::Simulink::XML::Reader &xrd
   )
  {
    constructFromXRD(xrd);
  }

  int BLGraph::constructFromXRD
  (
   ::Simulink::XML::Reader &xrd
   )
  {
    ::std::map< ::xml_schema::string,blnode_T*> nodemap;

    const ::Simulink::XML::block_map_T &blockmap = xrd.block_map();
    ::Simulink::XML::block_map_const_iterator bmi;
 
    // NODE
    for (bmi = blockmap.begin(); bmi != blockmap.end(); ++bmi){
      ::Simulink::XML::BlockInfo b_info = bmi->second;
      ::SimulinkModel::XSD::block_T *p_block = b_info.block();

#ifdef __DEBUG_MESSAGE__
      ::std::cerr << p_block->name() << std::endl;
#endif
      blnode_T *p_node = createNode(p_block);
      if( p_node == NULL ){
	// error
	continue;
      } else {
	// 連想配列に追加
	nodemap[p_block->name()] = p_node;
      }
    }

    // サブシステムによる階層構造情報追加
    for (bmi = blockmap.begin(); bmi != blockmap.end(); ++bmi){
      if( bmi->second.block()->blocktype() == "SubSystem" ){
	::std::map< ::xml_schema::string,blnode_T*>::iterator parent 
	  = nodemap.find(bmi->second.block()->name());
	if(parent == nodemap.end() ) continue;

	::SimulinkModel::XSD::block_T::blocks_sequence blkssq = bmi->second.block()->blocks();
	::SimulinkModel::XSD::block_T::blocks_iterator blksit;
	for(blksit = blkssq.begin(); blksit != blkssq.end(); ++blksit){
	  ::SimulinkModel::XSD::blocks_T::block_sequence cbseq = blksit->block();

	  ::SimulinkModel::XSD::blocks_T::block_const_iterator bsi = cbseq.begin();
	  if ( bsi == cbseq.end() ) continue;
	  ::std::map< ::xml_schema::string,blnode_T*>::iterator child
	      = nodemap.find(bsi->name());
	  if(child == nodemap.end() ) continue;
	  parent->second->p_child = child->second;
	  child->second->p_parent = parent->second;
	
	  blnode_T *before_child = child->second;
	  for(++bsi; bsi != cbseq.end(); ++bsi){// <sm:blocks>のイテレーション
	    child = nodemap.find(bsi->name());
	    if(child == nodemap.end() ) continue;
	    child->second->p_parent = parent->second;
	    before_child->p_sibling = child->second;
	    before_child = child->second;
	  }// end for <block> in <sm:blocks>
	}// end for <sm:blocks> in <block>
      }// end if subsystem
    }// end for <block>

    // EDGE
    for (bmi = blockmap.begin(); bmi != blockmap.end(); ++bmi){// <block>のイテレーション
      ::SimulinkModel::XSD::block_T *p_block = bmi->second.block();
      if( p_block == NULL ) continue;
      ::SimulinkModel::XSD::block_T *p_sblock = p_block;
      ::SimulinkModel::XSD::block_T *p_tblock = NULL;
#ifdef __DEBUG_MESSAGE__
      ::std::cerr<< "**EDGE** Block name: " << p_block->name() << ::std::endl;
#endif
     
      ::SimulinkModel::XSD::block_T::output_iterator  bii(p_block->output().begin());
      for(/* No initialize */; bii != p_block->output().end(); ++bii){// <output>のイテレーション
#ifdef __DEBUG_MESSAGE__
	    ::std::cerr << "1:bii->port " << bii->port() << ::std::endl;
#endif

	::SimulinkModel::XSD::ioport_T::connect_const_iterator cci(bii->connect().begin());
	for(/* No initialize*/; cci != bii->connect().end(); ++cci){// <connect>のイテレーション
	  ::Simulink::XML::IOPort *in_port = xrd.find_input_port(cci->block(), cci->port());
#ifdef __DEBUG_MESSAGE__
	  ::std::cerr << "  searching block: " << cci->block()
		      << " port: " << cci->port()
		      << " from port: " << bii->port()  << ::std::endl;
#endif
	  if(in_port == NULL) continue;
#ifdef __DEBUG_MESSAGE__
	  ::std::cerr << "  ... found!" << ::std::endl;
#endif
	  
	  p_tblock = in_port->block_tag();

	  //////////////////////////////
	  // サブシステム考慮
	  // 始点側
	  if( p_block->blocktype() == "SubSystem" ){
	    ::Simulink::XML::BlockInfo *pInfo = xrd.find_block(bii->port());
#ifdef __DEBUG_MESSAGE__
	    ::std::cerr << "2:bii->port " << bii->port() << ::std::endl;
#endif
	    if( pInfo == NULL ) continue;
	    if(isSubSystemBlockAtomic(p_sblock)){
	      p_sblock = pInfo->block();
	    } else {
	      p_sblock = pInfo->block();
	    }
#if 0
	    ::SimulinkModel::XSD::block_T::type_optional type = p_sblock->type();
	    if(type){// type要素あり：通常のサブシステムではない
	      ::xml_schema::string typestr = type.get();
#ifdef __DEBUG_MESSAGE__
	      ::std::cerr << "    Subsystem type: " << typestr << ::std::endl;
#endif
	      if(typestr == "iterator"){// For iterator subsystem;
		p_sblock = pInfo->block();
	      } else if (typestr    == "triggered" 
			 || typestr == "enabled"
			 || typestr == "atomic"
			 || typestr == "action"){// Triggered & Enabled subsystem.
		p_sblock = pInfo->block();
	      } else {
		p_sblock = pInfo->block();
	      }
	    } else {// 通常のサブシステム
	      p_sblock = pInfo->block();
	    }
#endif// if 0
#ifdef __DEBUG_MESSAGE__
	    std::cerr << "  From SUBSYSTEM: " << p_sblock->name() << "==> ???" << std::endl;
#endif
	  } // end 始点側

	  // 終点側
	  if( p_tblock->blocktype() == "SubSystem" ){
	    ::Simulink::XML::BlockInfo *pInfo = xrd.find_block(in_port->port());
	    if( pInfo == NULL ) continue;
#if 1
	    if(isSubSystemBlockAtomic(p_tblock)){
	      // もう一本エッジを追加
	      ::SimulinkModel::XSD::block_T *p_e2_sblock = p_tblock;
	      ::SimulinkModel::XSD::block_T *p_e2_tblock = pInfo->block();
	      blnode_T *s_node = nodemap[p_e2_sblock->name()];
	      blnode_T *t_node = nodemap[p_e2_tblock->name()];
	      createEdge(s_node, t_node);
	    } else {
	      p_tblock = pInfo->block();
	    }
#endif
#if 0
	    ::SimulinkModel::XSD::block_T::type_optional type = p_tblock->type();
	    if(type){// type要素あり：通常のサブシステムではない
	      ::xml_schema::string typestr = type.get();
#ifdef __DEBUG_MESSAGE__
	      ::std::cerr << "    Subsystem type: " << typestr << ::std::endl;
#endif

	      if(typestr == "iterator"){// For iterator subsystem;
		// もう一本エッジを追加
		::SimulinkModel::XSD::block_T *p_e2_sblock = p_tblock;
		::SimulinkModel::XSD::block_T *p_e2_tblock = pInfo->block();
		blnode_T *s_node = nodemap[p_e2_sblock->name()];
		blnode_T *t_node = nodemap[p_e2_tblock->name()];
		createEdge(s_node, t_node);
	      } else if(typestr    == "triggered"
			|| typestr == "enabled"
			|| typestr == "atomic"
			|| typestr == "action"){// Triggered & Enabled subsystem.
		// もう一本エッジを追加
		::SimulinkModel::XSD::block_T *p_e2_sblock = p_tblock;
		::SimulinkModel::XSD::block_T *p_e2_tblock = pInfo->block();
		blnode_T *s_node = nodemap[p_e2_sblock->name()];
		blnode_T *t_node = nodemap[p_e2_tblock->name()];
		createEdge(s_node, t_node);		
	      } else {
		p_tblock = pInfo->block();
	      }
	    } else {// 通常のサブシステム
	      p_tblock = pInfo->block();
	    }
#endif// if 0
#ifdef __DEBUG_MESSAGE__
	    std::cerr << "  To SUBSYSTEM: ??? ==>" << p_tblock->name() << std::endl;
#endif
	  } //end 終点側

	  blnode_T *s_node = nodemap[p_sblock->name()];
	  blnode_T *t_node = nodemap[p_tblock->name()];
	  createEdge(s_node, t_node);
	} // <connect>
      }// <output>
    }// end EDGE

    /* Isolated Subsystem問題対応  2015/02/22 kohei-y */
    ::std::vector<blnode_T*>::const_iterator ni;
    for(ni = m_node_list.begin(); ni != m_node_list.end(); ++ni){
      blnode_T *p_node = (*ni);
      if(p_node->p_block->blocktype() == "SubSystem" && !(p_node->p_block->type())){
	continue;
      }
      // 入力エッジがなく、モデルのルート上のブロックでないものは
      // isolated Subsystemである
      if(p_node->p_in_edge == NULL && p_node->p_parent != NULL){
	blnode_T *parent = p_node->p_parent;
	bool do_connect_flg = false;
	while(parent){// parentを再帰的にたどるように変更 2016/03/03 kohei-y
	  if (isSubSystemBlockAtomic(p_node->p_parent->p_block)){
	    do_connect_flg = true;
	    break;
	  }
	  parent = parent->p_parent;
	}
	// Isolated Subsystemのうち、atomic性のあるもののみを処理
	if(do_connect_flg){
	  bledge_T *p_edge = createEdge(p_node->p_parent, p_node);
	  if(p_edge){
	    p_edge->type = EDGE_CONTROL;
	  }
	}
      }
    }
    
    
    return 0;
  }

  blnode_T* BLGraph::createNode
  (
   ::SimulinkModel::XSD::block_T* p_block/* = NULL*/
   )
  {
    blnode_T* p_node = new blnode_T();
    if(!p_node) return NULL;
    static int callcnt = 0;

    p_node->p_block = p_block;
    p_node->index = callcnt++;

    m_node_list.push_back(p_node);
#ifdef __DEBUG_MESSAGE__
    ::std::cerr << "Add node: " << ::std::endl;
#endif
    return p_node;
  } // createNode

  bledge_T* BLGraph::createEdge
  (
   blnode_T* p_s_node, // 始点側ノード
   blnode_T* p_t_node // 終点側ノード
   )
  {
    // 引数に渡されたポインタはグラフ上にあるノードを指しているか？
    ::std::vector<blnode_T*>::iterator i_node;
    // 始点側
    i_node = find(m_node_list.begin(), m_node_list.end(), p_s_node);
    if(i_node == m_node_list.end()) return NULL;
    // 終点側
    i_node = find(m_node_list.begin(), m_node_list.end(), p_t_node);
    if(i_node == m_node_list.end()) return NULL;
      
    // memory allocation
    bledge_T* p_edge = new bledge_T();
    if(!p_edge) return NULL;

    // ノードのセット
    p_edge->p_s_node = p_s_node;
    p_edge->p_t_node = p_t_node;

#ifdef _INSERT_EDGE_AT_TAIL
    // {in,out}_edgeへの挿入位置を探索
    // out側
    bledge_T** p_insert_edge = &(p_s_node->p_out_edge);
    while(*p_insert_edge != NULL) p_insert_edge = &((*p_insert_edge)->p_out_edge);
    *p_insert_edge = p_edge;
    // in側
    p_insert_edge = &(p_t_node->p_in_edge);
    while(*p_insert_edge != NULL) p_insert_edge = &((*p_insert_edge)->p_in_edge);
    *p_insert_edge = p_edge;

    p_edge->p_in_edge = NULL;
    p_edge->p_out_edge = NULL;
#else
    // 先頭挿入版
    // out側
    p_edge->p_out_edge = p_s_node->p_out_edge;
    p_s_node->p_out_edge = p_edge;
    // in側
    p_edge->p_in_edge = p_t_node->p_in_edge;
    p_t_node->p_in_edge = p_edge;
#endif

    // edgeのタイプの決定
    // まだ、CONTROLの判定式を作っていない。
    ::std::string tntype = p_t_node->p_block->blocktype();
    if( isTBTypeInheritNext(tntype) )
      p_edge->type = EDGE_INHERIT;
    else if( isTBTypeUpdate(tntype) )
      p_edge->type = EDGE_UPDATE;
    else if( isTBTypeControl(tntype) )
      p_edge->type = EDGE_CONTROL;
    else
      p_edge->type = EDGE_DATA;

    // リストに追加
    m_edge_list.push_back(p_edge);

#ifdef __DEBUG_MESSAGE__
    ::std::cerr << "Add edge: " << p_s_node->p_block->name() << "->" << p_t_node->p_block->name()  << ::std::endl;
#endif    
    return p_edge;
  } // createEdge

  int BLGraph::deleteNode
  (
   blnode_T* p_node
   )
  {
    ::std::vector<blnode_T*>::iterator i_node =
      find(m_node_list.begin(), m_node_list.end(), p_node);
    if(i_node == m_node_list.end()){
      //削除対象ノードがリストにない
      return 1;
    }
      
    bledge_T** p_del_edge = &(p_node->p_out_edge);
    bledge_T** p_next_edge;
    while(*p_del_edge != NULL){
      p_next_edge = &((*p_del_edge)->p_out_edge);
      deleteEdge(*p_del_edge);
      p_del_edge = p_next_edge;
    }

    p_del_edge = &(p_node->p_in_edge);
    while(*p_del_edge != NULL){
      p_next_edge = &((*p_del_edge)->p_in_edge);
      deleteEdge(*p_del_edge);
      p_del_edge = p_next_edge;
    }
      
    m_node_list.erase(i_node);
    delete(p_node);
    return 0;
  }// deleteNode

  int BLGraph::deleteEdge
  (
   bledge_T* p_edge
   )
  {
    ::std::vector<bledge_T*>::iterator i_edge = 
      find(m_edge_list.begin(), m_edge_list.end(), p_edge);
    if(i_edge == m_edge_list.end()){
      // 削除対象エッジがリストにない
      return 1;
    }
      
    // 始点側のノードの p_out_edge の関係が崩れないように
    if( p_edge->p_s_node->p_out_edge == p_edge ){
      p_edge->p_s_node->p_out_edge = p_edge->p_out_edge;
    } else {
      bledge_T** p_prev_edge = &(p_edge->p_s_node->p_out_edge);
      bledge_T** p_next_edge = &((*p_prev_edge)->p_out_edge);
      while( *p_next_edge != NULL ){
	if (*p_next_edge == p_edge){
	  (*p_prev_edge)->p_out_edge = p_edge->p_out_edge;
	  break;
	}// end if
	p_prev_edge = p_next_edge;
	p_next_edge = &((*p_next_edge)->p_out_edge);
      }// end while
    }

    // 終点側のノードの p_in_edge の関係が崩れないように
    if( p_edge->p_t_node->p_in_edge == p_edge ){
      p_edge->p_t_node->p_in_edge = p_edge->p_in_edge;
    } else {
      bledge_T** p_prev_edge = &(p_edge->p_t_node->p_in_edge);
      bledge_T** p_next_edge = &((*p_prev_edge)->p_in_edge);
      while( *p_next_edge != NULL ){
	if (*p_next_edge == p_edge){
	  (*p_prev_edge)->p_in_edge = p_edge->p_in_edge;
	  break;
	}// end if
	p_prev_edge = p_next_edge;
	p_next_edge = &((*p_next_edge)->p_in_edge);
      }// end while
    }
      
    m_edge_list.erase(i_edge);
    delete(p_edge);
    return 0;
  } // deleteEdge
  
  ::std::vector<blnode_T*> BLGraph::getNodeVector
  (void) const
  {
    return m_node_list;
  } // getNodeVector

  ::std::vector<bledge_T*> BLGraph::getEdgeVector
  (void) const
  {
    return m_edge_list;
  } // getEdgeVector

#ifdef __BLG_WITH_GRAPHVIZ__
#define COLORS 16
#define CNLENGTH 24
  // 20150826 yamaguchi
  // 文字列の出力フラグ追加
  void BLGraph::dumpDotFile
  (
   ::std::string filename,
   unsigned int mode
   ) const
  {
    // 201507某日：グラフ色付け対応 @kohei-y
    // とりあえず16色まで色分けします
    char colorstr[COLORS][CNLENGTH] = {
      "brown1", "burlywood1", "cadetblue1", "chartreuse1", "chocolate1", "cornsilk1"
      , "brown3", "burlywood3", "cadetblue3", "chartreuse3", "chocolate3", "cornsilk3"
      , "lightpink", "lightsalmon", "lightseagreen", "lightskyblue"};
    ::std::vector<std::string> penames;

    char empstr[] = "";
    ::std::map< blnode_T*, Agnode_t*  > blagmap;
    //    Agraph_t *ag = agopen("blgraph", AGDIGRAPH);
    char blgstr[] = "blgraph";
    Agraph_t *ag = agopen(blgstr, Agdirected, &AgDefaultDisc);
    
    char stylestr[]= "style";
    char edgecolorstr[]= "color";

    // 20150703 yamaguchi
    // BLGraphで読み込んだ順番をグラフ上に出力
    //sprintf(lbl,"[%d]\n%s", i, (*ni)->p_block->name().c_str());
    const bool printTaskNumFlg = (mode & DDF_PRINT_BLG_ID)? true: false;
    const bool printTaskNameFlg = (mode & DDF_PRINT_TASK_NAME)? true: false;
    const bool printTaskPerfFlg = (mode & DDF_PRINT_TASK_PERF)? true: false;
#ifdef __DEBUG_MESSAGE__
    ::std::cerr << "<dumpDotFile> printTaskNumFlg: " << (printTaskNumFlg? "true":"false") << ::std::endl;
    ::std::cerr << "<dumpDotFile> printTaskNameFlg: " << (printTaskNameFlg? "true":"false") << ::std::endl;
    ::std::cerr << "<dumpDotFile> printTaskPerfFlg: " << (printTaskPerfFlg? "true":"false") << ::std::endl;
#endif

    ::std::vector<blnode_T*>::const_iterator ni;
    int i = 0;
    for(ni = m_node_list.begin(); ni != m_node_list.end(); ++ni){
      ::std::string blkname;
      char nn[32];
      sprintf(nn, "block%u", i++);
      Agnode_t *n = agnode(ag, nn, 1);
      char lbl[512];
      lbl[0] = '\0';
      bool notFirstFlg = false;

      if (printTaskNumFlg){
	sprintf(lbl + strlen(lbl),"[%d]", i);
	notFirstFlg = true;
      }
      if (printTaskNameFlg){
	sprintf(lbl + strlen(lbl),"%s%s", notFirstFlg? "\n":"", (*ni)->p_block->name().c_str());
	notFirstFlg = true;
      }
      if (printTaskPerfFlg){// パフォーマンス情報取得
	::SimulinkModel::XSD::block_T::performance_sequence ps = (*ni)->p_block->performance();
	::SimulinkModel::XSD::block_T::performance_iterator pi;
	double perf = 0.0;
	if( ps.begin() != ps.end() ){
	  for(pi =  ps.begin() ; pi != ps.end() ; ++pi){
	    if( (*pi).type() == "task" ) perf += (*pi).typical();
	    if( (*pi).type() == "update" ) perf += (*pi).typical();
	  }
	} else {
	  perf = 1;
	}
	sprintf(lbl + strlen(lbl),"%s%.1f[cycles]", notFirstFlg? "\n":"", perf);
	notFirstFlg = true;
      }
      
      {
	if (!notFirstFlg){
	  lbl[0]=' ';lbl[1] = '\0';
	}
	char labelstr[] = "label";
	agsafeset(n, labelstr, lbl, empstr);
      }

      ::SimulinkModel::XSD::block_T::peinfo_optional peinfo = (*ni)->p_block->peinfo();
      if( peinfo && (mode & DDF_COLORED_NODE) ){// peifnoが存在するときのみ色付け
	char filledstr[] = "filled";
	::std::string peinfoVar = peinfo.get();
	agsafeset(n, stylestr, filledstr, empstr);
	
	int coloridx = 0;
	int pnsize = penames.size();
	for(coloridx = 0; coloridx < pnsize; coloridx++){
	  if(peinfoVar == penames[coloridx]){// すでに同じ文字列が使われているか
	    break;
	  }
	}//end for
	
	if(coloridx >= pnsize){// 新たなpeinfoの文字列
	  penames.push_back(peinfoVar);
	}

	char fcstr[] = "fillcolor";
	agsafeset(n, fcstr, colorstr[coloridx%COLORS], empstr);
      }

      blagmap[*ni] = n;
    }

    ::std::vector<bledge_T*>::const_iterator ei;
    for(ei = m_edge_list.begin(); ei != m_edge_list.end(); ++ei){
      blnode_T *n1 = (*ei)->p_s_node;
      blnode_T *n2 = (*ei)->p_t_node;

      Agedge_t *e = agedge(ag, blagmap[n1], blagmap[n2], empstr, 1);
      char styleattr[8];
      char colorattr[6];
      strncpy(styleattr, ( (*ei)->type == EDGE_UPDATE )? "dashed" : "solid", 8);
      strncpy(colorattr, ( (*ei)->type == EDGE_CONTROL )? "red" : "black", 8);

      agsafeset(e, stylestr, styleattr, empstr);
      agsafeset(e, edgecolorstr, colorattr, empstr);
      (void)e;
    }

    FILE *fp;
    if( filename.length() == 0 || filename == "-"){
      fp = stdout;
    } else {
      fp = fopen(filename.c_str(), "wt");
    }
    agwrite(ag,fp);
  } // dumpDotFile
#endif // 位置を移動

  inline bool BLGraph::isTBTypeInheritNext
  (
   const ::xml_schema::string &type
   ) const
  {
    if( type == "SubSystem" || type == "Inport" || type == "Outport")
      return true;
    
    return false;
  }// isTBTypeInheritNext
  
  inline bool BLGraph::isTBTypeUpdate
  (
   const ::xml_schema::string & type
   ) const
  {
    if( type == "UnitDelay" || type == "Memory")
      return true;
    
    return false;
  } // isTBTypeUpdate

  inline bool BLGraph::isTBTypeControl
  (
   const ::xml_schema::string & type
   ) const
  {
    if( type == "TriggerPort" || type == "EnablePort" || type == "ActionPort")
      return true;
    
    return false;
  } // isTBTypeControl

  inline bool BLGraph::isSubSystemBlockAtomic
  (
   const ::SimulinkModel::XSD::block_T *p_block
   ) const
  {
    bool retval = false;
    ::SimulinkModel::XSD::block_T::type_optional type = p_block->type();
    if(type){// type要素あり：通常のサブシステムではない
      ::xml_schema::string typestr = type.get();
#ifdef __DEBUG_MESSAGE__
      ::std::cerr << "    Subsystem type: " << typestr << ::std::endl;
#endif
      if(typestr    == "iterator"// For Iterator Subsystem
	 || typestr == "atomic"// Atomic Sybsystem
	 || typestr == "triggered"// Triggereed Subsystem
	 || typestr == "enabled"// Enable Subsystem
	 || typestr == "action"// (If-)Atcion Subsystem
	 ) {
	retval = true;
      }
    }
    return retval;
  }// isSubSystemBlockAtomic
} // namespace BLGraph
