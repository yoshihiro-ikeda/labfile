#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>

#include <xercesc/dom/DOM.hpp>

#include "SimulinkXML.h"

#include <xsd/cxx/xml/string.hxx>

using namespace std;
using namespace SimulinkModel;
using namespace SimulinkModel::XSD;
using namespace Simulink;
using namespace Simulink::XML;

#define WITH_CGRAPH
#include <graphviz/types.h>

#ifndef WITH_CGRAPH
#include <graphviz/graph.h>
#endif

#include <unistd.h>

typedef ::std::map< unsigned int, Agnode_t* > nodemap_T;
typedef nodemap_T::iterator nodemap_iterator;
typedef nodemap_T::const_iterator nodemap_const_iterator;

#if defined(__MINGW32__) || defined(__MINGW64__)
static int
mingw_afread (void *chan, char *buf, int bufsize)
{
  return (int)fread (buf, bufsize, 1, (FILE *)chan);
}

static int
mingw_putstr (void *chan, const char *str)
{
  return (int)fputs (str, (FILE *)chan);
}

static int
mingw_flush (void *chan)
{
  return fflush ((FILE *)chan);
}
#endif

#if 1
void
output_node (Agraph_t* ag,
	     Reader& xrd, const blocks_T& bs, nodemap_T& nodemap)
{
  char attr[32];
  char val[32];
  char name[1024];
  char empstr[] = "";

  for (blocks_T::block_const_iterator i (bs.block ().begin ());
       i != bs.block ().end (); i++)
    {
      const block_T& b = *i;

      Agraph_t *xag = ag;

      if (b.blocktype() == "SubSystem")
	{
	  strncpy (name, b.name ().c_str (), sizeof name);
#ifdef WITH_CGRAPH
	  xag = agsubg (ag, name, 1);
#else
	  xag = agsubg (ag, name);
#endif
	  strcpy (attr, "label");
	  agsafeset (xag, attr, name, empstr);

	  for (block_T::blocks_const_iterator j (b.blocks ().begin ());
	       j != b.blocks ().end (); j++)
	    output_node (xag, xrd, *j, nodemap);
	}

      if (b.forward().size() || b.backward().size())
	{
	  const BlockInfo* binfo = xrd.find_block (b.name());

	  sprintf (name, "t%u", binfo->id());
#ifdef WITH_CGRAPH
	  Agnode_t* n = agnode (xag, name, 1);
#else
	  Agnode_t* n = agnode (xag, name);
#endif
	  nodemap.insert(::std::make_pair(binfo->id(), n));
	  sprintf (name, "t%u\\n%s",
		   binfo->id(), b.name().c_str());
	  strcpy (attr, "label");
	  agsafeset (n, attr, name, empstr);
	  if (b.blocktype() == "Inport" || b.blocktype() == "Outport")
	    {
	      strcpy (attr, "shape");
	      strcpy (val, "box");
	      agsafeset (n, attr, val, empstr);
	    }
	  else if (b.blocktype() == "SubSystem")
	    {
	      strcpy (attr, "style");
	      strcpy (val, "filled");
	      agsafeset (n, attr, val, empstr);
	      strcpy (attr, "fillcolor");
	      strcpy (val, "plum");
	      agsafeset (n, attr, val, empstr);
	    }
	}
    }
}
#endif

int
main(int argc, char * const *argv)
{
  int c;
  int lr = 0;
  int do_dump = 0;
  bool xml_validation = true;
#if defined(__MINGW32__) || defined(__MINGW64__)
  Agiodisc_t mingw_iodisc = {
    .afread = mingw_afread,
    .putstr = mingw_putstr,
    .flush = mingw_flush,
  };
  Agdisc_t mingw_disc = {
    .mem = &AgMemDisc,
    .id = &AgIdDisc,
    .io = &mingw_iodisc,
  };
#define MY_DISC	(&mingw_disc)
#else
#define MY_DISC (&AgDefaultDisc)
#endif

  while ((c = getopt (argc, argv, "ldn")) != -1)
    {
      switch (c)
	{
	case 'l':
	  lr = 1;
	  break;

	case 'd':
	  do_dump = 1;
	  break;

	case 'n':
	  xml_validation = false;
	  break;

	case '?':
	  ::std::cerr << "usage: "
		      << argv[0]
		      << " [-n] [-l] input.xml [output.dot]" << ::std::endl;
	  return 1;
	}
    }

  argv += optind - 1;
  argc -= optind - 1;

  if ((do_dump && argc < 3)
      || argc < 2)
    return 1;

  Reader xrd (argv[1], xml_validation);

  if (!xrd)
    return 1;

  if (do_dump)
    xrd.dump ();

#if 0
  for (block_map_iterator bmi (xrd.block_map().begin ());
       bmi != xrd.block_map ().end (); bmi++)
    {
      if (bmi->second.has_update ())
	xrd.find_loop (bmi->second.id ());
    }
#endif

#ifndef WITH_CGRAPH
  aginit();
#endif

  char empstr[] = "";

  char attr[32] = "rankdir";
  char val[32] = "testout";

#ifdef WITH_CGRAPH
  Agraph_t* ag = agopen (val, Agdirected, MY_DISC);
#else
  Agraph_t* ag = agopen (val, AGDIGRAPH);
#endif

  if (lr)
    {
      strcpy (val, "LR");
      agsafeset (ag, attr, val, empstr);
    }

  nodemap_T nodemap;

#if 1
  output_node (ag, xrd, xrd.xml_blocks(), nodemap);
#else
  for (block_map_const_iterator i (xrd.block_map().begin());
       i != xrd.block_map().end(); i++)
    {
      const BlockInfo& bi = i->second;
      if (bi.block()->forward().size()
	  || bi.block()->backward().size())
	{
	  char name[1024];
	  sprintf (name, "t%u", bi.id());
#ifdef WITH_CGRAPH
	  Agnode_t* n = agnode (ag, name, 1);
#else
	  Agnode_t* n = agnode (ag, name);
#endif
	  nodemap.insert(::std::make_pair(bi.id(), NodeEnt (n)));
	  sprintf (name, "t%u\\n%s",
		   bi.id(), bi.block()->name().c_str());
	  strcpy (attr, "label");
	  agsafeset (n, attr, name, empstr);
	  if (bi.block()->blocktype() == "Inport"
	      || bi.block()->blocktype() == "Outport")
	    {
	      strcpy (attr, "shape");
	      strcpy (val, "box");
	      agsafeset (n, attr, val, empstr);
	    }
	  else if (bi.block()->blocktype() == "SubSystem")
	    {
	      strcpy (attr, "style");
	      strcpy (val, "filled");
	      agsafeset (n, attr, val, empstr);
	      strcpy (attr, "fillcolor");
	      strcpy (val, "plum");
	      agsafeset (n, attr, val, empstr);
	    }
	}
    }
#endif

  for (block_map_const_iterator i (xrd.block_map().begin());
       i != xrd.block_map().end(); i++)
    {
      const block_T* b = i->second.block();

      nodemap_const_iterator ni = nodemap.find(i->second.id());
      if (ni == nodemap.end ())
	continue;

      Agnode_t *nn1 = ni->second;

      if (b->forward().size())
	{
	  for (block_T::forward_const_iterator j (b->forward().begin());
	       j != b->forward().end(); j++)
	    {
	      block_map_const_iterator
		fi (xrd.block_map().find(j->block()));
	      if (fi != xrd.block_map().end())
		{
		  Agnode_t *nn2 = nodemap.find(fi->second.id())->second;
#ifdef WITH_CGRAPH
		  Agedge_t* e = agedge (ag, nn1, nn2, empstr, 1);
#else
		  Agedge_t* e = agedge (ag, nn1, nn2);
#endif

		  char label[1024];
		  char *p = label;
		  for (block_T::var_const_iterator vi (j->var().begin());
		       vi != j->var().end(); vi++)
		    {
		      if (p != label)
			*p++ = ',';
		      const var_T::start_optional& st = vi->start();
		      const var_T::end_optional& ed = vi->end();
		      const var_T::size_optional& sz = vi->size();

		      ::std::string s (vi->name());
		      ::std::ostringstream oo;

		      if (st && ed)
			oo << '[' << *st << '-' << *ed << ']';
		      else if (st)
			oo << '[' << *st << ']';
		      else if (sz)
			oo << "[sz=" << *sz << ']';
		      s += oo.str();
		      ::std::cout << "label: " << s << ::std::endl;
		      strcpy (p, s.c_str());
		      p += strlen (p);
		    }
		  *p = 0;
		  strcpy (attr, "label");
		  agsafeset (e, attr, label, empstr);
		}
	    }
	}
      else if (b->blocktype () == "SubSystem")
	{
	  block_map_const_iterator ti = xrd.block_map ().find (b->name());
	  if (ti != xrd.block_map ().end ())
	    {
	      const BlockInfo& bi = ti->second;

	      for (block_list_const_iterator
		     j (bi.lower_block ().begin ());
		   j != bi.lower_block ().end (); j++)
		{
		  const BlockInfo* xi = *j;

		  nodemap_const_iterator k = nodemap.find (xi->id ());
		  if (k == nodemap.end ())
		    continue;

		  Agnode_t *nn2 = k->second;

#ifdef WITH_CGRAPH
		  Agedge_t* e = agedge (ag, nn1, nn2, empstr, 1);
#else
		  Agedge_t* e = agedge (ag, nn1, nn2);
#endif
		  strcpy (attr, "color");
		  strcpy (val, "red");
		  agsafeset (e, attr, val, empstr);
		  strcpy (attr, "style");
		  strcpy (val, "dashed");
		  agsafeset (e, attr, val, empstr);
		}
	    }
	}
    }

  if (argv[2])
    {
      FILE *fp = fopen (argv[2], "w");
      agwrite (ag, fp);
      fclose (fp);
      agclose(ag);
    }
  else
    agwrite (ag, stdout);
  return 0;
}
