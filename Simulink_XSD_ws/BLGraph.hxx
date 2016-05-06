////////////////////////////////////////////////////////////
// BLGraph.h / BLGraph.cxx
// RTWコードとbindしたBL XMLファイルからグラフ構造を作成
// kohei-y
//

#include <vector>
#include <xsd/cxx/xml/string.hxx>

#include "SimulinkXML.h"

#define __BLG_WITH_GRAPHVIZ__

namespace BLG {
  ////////////////////////////////////////
  //
  // 列挙体定義
  //
  enum edge_type {
    EDGE_DATA,
    EDGE_CONTROL,
    EDGE_UPDATE,
    EDGE_INHERIT,
    EDGE_INVALID = -1
  };
  ////////////////////////////////////////
  //
  // 構造体定義
  // ユーザーはいじらないでね
  //
  //struct bl_node;
  //struct bl_edge;
  
  struct blnode_T{
    ::SimulinkModel::XSD::block_T* p_block;
    struct bledge_T* p_in_edge;
    struct bledge_T* p_out_edge;
    struct blnode_T* p_parent;
    struct blnode_T* p_sibling;
    struct blnode_T* p_child;
    int index;
    void *hook;
    blnode_T(){
      p_in_edge  = NULL;
      p_out_edge = NULL;
      p_parent   = NULL;
      p_sibling  = NULL;
      p_child    = NULL;
      hook = NULL;
    };
  } ;
  
  struct bledge_T{
    edge_type type;
    struct blnode_T* p_s_node;
    struct blnode_T* p_t_node;
    struct bledge_T* p_in_edge;
    struct bledge_T* p_out_edge;
    void *hook;
    bledge_T(){
      type = EDGE_DATA;
      p_s_node   = NULL;
      p_t_node   = NULL;
      p_in_edge  = NULL;
      p_out_edge = NULL;
      hook = NULL;
    }
  } ;
  
  ////////////////////////////////////////
  //
  // クラス BLGraph
  //
  class BLGraph{
    ////////////////////
    //
    // メンバ変数
    //  private:
  protected:
    ::std::vector<blnode_T*> m_node_list;
    ::std::vector<bledge_T*> m_edge_list;
    //  public:

    ////////////////////
    //
    // メンバ関数
    //  private:
    //  protected:
  public:
    // コンストラクタとデストラクタ
    BLGraph(::Simulink::XML::Reader &xrd);

    ////////////////////
    // constructFromXML
    // [概要] XMLファイルからBLGraphを作成
    // [引数]
    //    filename : 読み込むファイル
    // [返り値] なし
    // [備考]
    //    TODO: 二重呼び出しの防止, マジックナンバーの撤廃
    int constructFromXRD
    (
     ::Simulink::XML::Reader &xrd
     );
    
    ////////////////////
    // createNode
    // [概要] ノードを作成する。
    // [引数]
    //   block_T* p_block：ノードと対応するブロックの情報をもつ
    //                     block_Tへのポインタ
    // [返り値]
    //   作成に成功：作成したノードへのポインタ
    //   作成に失敗：NULL
    //
    blnode_T* createNode
    (
     ::SimulinkModel::XSD::block_T* p_block = NULL// ノードと対応するブロック情報
     );

    ////////////////////
    // createEdge
    // [概要] エッジを作成する。
    // [引数]
    //   p_s_node：始点側のノードへのポインタ
    //   p_t_node：終点側のノードへのポインタ
    // [返り値]
    //   作成に成功：作成したエッジへのポインタ
    //   作成に失敗：NULL
    // [備考]
    //   始点側、終点側のnodeIDは、それぞれvalidである必要があります。
    bledge_T* createEdge
    (
     blnode_T* p_s_node, // 始点側ノードのポインタ
     blnode_T* p_t_node // 終点側ノードのポインタ
     );

    ////////////////////
    // deleteNode
    // [概要] ノードを削除する。
    // [引数]
    //   p_node：削除対象のノードへのポインタ
    // [返り値]
    //   削除に成功：0
    //   削除に失敗：1
    // [備考]
    //   削除対象のノード
    //
    int deleteNode
    (
      blnode_T* p_node
    );

    ////////////////////
    // deleteEdge
    // [概要] エッジを削除する。
    // [引数]
    //   p_edge：削除対象のエッジへのポインタ
    // [返り値]
    //   削除に成功：0
    //   削除に失敗：1
    // [備考]
    //   p_out_edge, p_in_edgeによる前方/後方探索の関係が
    //   崩れないように削除を行います。
    int deleteEdge
    (
      bledge_T* p_edge
    );

    ////////////////////
    // getNodeVector
    // [概要] ノードのベクトルを返す
    // [引数] なし
    // [返り値] グラフに所属するノードのベクトル
    // [備考]
    //  m_node_listを返す
    ::std::vector<blnode_T*> getNodeVector
    ( void ) const;

    ////////////////////
    // getEdgeVector
    // [概要] エッジのベクトルを返す
    // [引数] なし
    // [返り値] グラフに所属するノードのベクトル
    // [備考]
    //  m_node_listを返す
    ::std::vector<bledge_T*> getEdgeVector
    ( void ) const;

#ifdef __BLG_WITH_GRAPHVIZ__
    enum {
      DDF_COLORED_NODE    = 0x1,
      DDF_PRINT_BLG_ID   = 0x2,
      DDF_PRINT_TASK_NAME = 0x4,
      DDF_PRINT_TASK_PERF = 0x8,
      DDF_ALL_ON = 0x15
    };
    ////////////////////
    // dumpDotFile
    // [概要] dot形式でグラフを出力
    // [引数]
    // filename 出力先ファイル名
    // printTaskNumFlg  trueの時、タスク番号をノードに表示します
    // printTaskNameFlg trueの時、タスクの名前をノードに表示します
    // [返り値] なし
    // [備考] 2015/08/27 printTaskNumFlg, printTaskNameFlgを引数に追加
    void dumpDotFile
    (
     ::std::string filename,
     unsigned int mode = DDF_ALL_ON
     ) const;
#endif

  private:
    ////////////////////
    // isTBTypeInheritNext
    // [概要] エッジの型を継承にするべきかどうかを判断
    // [引数] type エッジの終端側ノードのblocktype()
    // [返り値] true: 継承にするべき false: 継承にしないで
    // [備考] createEdgeがtypeを設定するために内部で利用する関数です。
    // ユーザは、enumerateのtypeを見てエッジの型を判断してください。
    inline bool isTBTypeInheritNext
    (
     const ::xml_schema::string & type
     ) const;

    ////////////////////
    // isTBTypeUpdate
    // [概要] エッジの型をUpdate Onlyにするべきかどうかを判断
    // [引数] type エッジの終端側ノードのblocktype()
    // [返り値] true: Update Only false: そうではない
    // [備考] createEdgeがtypeを設定するために内部で利用する関数です。
    // ユーザは、enumerateのtypeを見てエッジの型を判断してください。
    inline bool isTBTypeUpdate
    (
     const ::xml_schema::string &type
     ) const;

    ////////////////////
    // isTBTypeControl
    // [概要] エッジの型をControlにするべきかどうかを判断
    // [引数] type エッジの終端側ノードのblocktype()
    // [返り値] true: Control false: そうではない
    // [備考] createEdgeがtypeを設定するために内部で利用する関数です。
    // ユーザは、enumerateのtypeを見てエッジの型を判断してください。
    inline bool isTBTypeControl
    (
     const ::xml_schema::string &type
     ) const;

    ////////////////////
    // isSubSystemBlockAtomic
    // [概要] サブシステムがアトミック性のあるかどうかを判断
    // [引数] サブシステムブロックのblockへのポインタ
    // [返り値] true: サブシステム性あり false: なし
    // [備考] コンストラクタが内部で利用する関数です。
    // ユーザがこの情報を取得する手段は今のところありません。
    // また、アトミック性があるとは、Triggerなどによって強制的に
    // アトミック扱いされるものも含みます。
    inline bool isSubSystemBlockAtomic
    (
     const ::SimulinkModel::XSD::block_T *p_block
     ) const;
  };// end of Class BLGraph
}// end of namespace BLG

//関数説明テンプレート
    ////////////////////
    // functionName
    // [概要] 
    // [引数]
    // [返り値]
    // [備考]
