#include <iostream>
#include <string.h>
#include <assert.h>

#include "SimulinkXML.h"

#ifdef __GNUC__
// TR1 using BOOST Project
// libstdc++-V3 doesn't work
#include <boost/tr1/regex.hpp>
#else
#include <tr1/regex>
#endif

#ifdef USE_DMALLOC
#include <dmalloc.h>
#endif	// USE_DMALLOC

using namespace SimulinkModel;
using namespace SimulinkModel::XSD;

namespace Simulink
{
  namespace XML
  {
    unsigned int BlockInfo::seq = 0;

    BlockInfo*
    find_multirate_subsystem (const BlockInfo* binfo)
    {
      if (binfo == NULL)
	return NULL;

      BlockInfo* cur = binfo->upper_subsystem ();

      while (cur)
	{
	  if (cur->is_subsystem() &&
	      (cur->subsystem_type () == BlockInfo::TRIGGERED
	       || cur->subsystem_type () == BlockInfo::ENABLED))
	    return cur;
	  cur = cur->upper_subsystem ();
	}

      return NULL;
    }

    const char*
    nextline (const char* line, size_t& size)
    {
      const char* end = line + size;
      while (line < end)
	{
	  --size;
	  if (*line++ == '\n')
	    break;
	}
      return line;
    }

    const char*
    comment_check (const char*& beg, const char* end,
		   char& dir, char& type,
		   unsigned int& num, ::std::string& name)
    {
      try
	{
	  ::std::tr1::regex mark("^"
				 "/\\*"
				 "(<<<|>>>)"		// %1 -- dir
				 "[[:space:]]"
				 "([ESX])"		// %2 -- type
				 "[[:space:]]"
				 "([[:digit:]]+)"	// %3 -- num
				 "[[:space:]]"
				 "("			// %4 -- block
				 "none"
				 "|"
				 "([_[:alnum:]]+)"	// %5 -- name
				 "[[:space:]]"
				 "'<[^>]+>/[^']+'"
				 ")"			// %4(close)
				 "[[:space:]]"
				 "(<<<|>>>)"		// %6 -- dir
				 "\\*/");

	  ::std::tr1::cmatch mr;

	  if (::std::tr1::regex_search (beg, end, mr, mark))
	    {
	      if (*mr[1].first != *mr[6].first)
		return NULL;
	      dir = *mr[1].first;
	      type = *mr[2].first;
	      ::std::istringstream ss (mr[3]);
	      ss >> num;
	      if (mr[4] == "none")
		name = mr[4];
	      else
		name = mr[5];

	      beg = mr[0].first; // begin of match

	      const char* p = mr[0].second; // end of match
	      size_t s = end - p;
	      return nextline (p, s);
	    }
	}

      catch (const ::std::tr1::regex_error& e)
	{
	  ::std::cerr << "Error in " << __FUNCTION__ << ":"
		      << e.what() << ::std::endl;
	}
      catch (const ::std::bad_exception& e)
	{
	  ::std::cerr << "Error in " << __FUNCTION__ << ::std::endl;
	}
      catch (...)
	{
	  ::std::cerr << "Error in " << __FUNCTION__ << ::std::endl;
	}

      return NULL;
    }

    const char*
    cut_code (const char*& cbeg, const char* cend,
	      const char*& tbeg, const char*& tend,
	      char& type, unsigned int& num, ::std::string& block)
    {
      char xd;

      const char* n = comment_check (cbeg, cend, xd, type, num, block);
      if (n == NULL || xd != '<')
	return NULL;

      tbeg = n;			// after comment
      const char* r = n;

      while (r < cend)
	{
	  char xt;
	  unsigned int xn;
	  ::std::string xb;

	  n = comment_check (r, cend, xd, xt, xn, xb);
	  if (type == 'X')
	    {
	      if (n)
		{
		  tend = r;	// before comment
		  return r;	// before comment
		}
	      else
		{
		  tend = cend;	// end
		  return cend;	// end
		}
	    }
	  else if (n != NULL
		   && (xd == '>' && xt == type && xn == num && xb == block))
	    {
	      tend = r;		// before comment
	      return n;		// skip comment
	    }

	  break;
	}

      return NULL;
    }

    void
    codelist::process (const char* beg, const char* end)
    {
      while (beg < end)
	{
	  char type;
	  unsigned int num;
	  ::std::string block;
	  const char* tbeg = NULL;
	  const char* tend = NULL;
	  const char* e = cut_code (beg, end, tbeg, tend, type, num, block);
	  if (e == NULL)
	    break;
	  list.push_back (c_mark (beg, e, tbeg, tend, type, num, block));
	  beg = e;
	}
    }

    BlockInfo::BlockInfo(block_T* block, block_T* upper)
      : b_block (block), b_upper (upper), b_is_subsystem (false),
	b_has_update (false), b_is_sfunction (false),
	b_subsystem_type (NONE), b_upper_subsystem (NULL),
	b_top (NULL), b_top_subsystem (NULL),
	b_trigger_port (NULL), b_enable_port (NULL), b_action_port (NULL)
    {
      block_T::id_optional& oid = block->id ();
      if (oid)
	{
	  b_id = *oid;
	  if (seq < b_id)
	    seq = b_id;
	}
      else
	b_id = 0;
    }

    bool
    BlockInfo::is_contained (const BlockInfo* b) const
    {
      for (block_list_const_iterator bl (contain_block ().begin ());
	   bl != contain_block ().end (); bl++)
	{
	  if (b == *bl)
	    return true;
	}
      return false;
    }

    bool
    BlockInfo::is_contained (const block_T* b) const
    {
      for (block_list_const_iterator bl (contain_block ().begin ());
	   bl != contain_block ().end (); bl++)
	{
	  if (b == (*bl)->block ())
	    return true;
	}
      return false;
    }

    bool
    BlockInfo::is_atomic_subsystem (void) const
    {
      if ((subsystem_type () == ATOMIC
	   || subsystem_type () == ITERATOR)
	  && contain_block ().size () > 0)
	return true;
      const block_T::TreatAsAtomicUnit_optional&
	ao = block ()->TreatAsAtomicUnit ();
      if (ao && *ao == "on")
	return true;
      return false;
    }

    void
    BlockInfo::dump (void) const
    {
      ::std::cout << "id=" << id() << " Block=" << block()->name() << "\n";
      ::std::cout << "  BlockType=" << block ()->blocktype ();
      if (is_subsystem ())
	{
	  if (subsystem_type () == BlockInfo::ATOMIC)
	    ::std::cout << "[atomic]";
	  else if (subsystem_type () == BlockInfo::ENABLED)
	    ::std::cout << "[enabled]";
	  else if(subsystem_type () == BlockInfo::TRIGGERED)
	    ::std::cout << "[triggered]";
	  else if (subsystem_type () == BlockInfo::ENABLED_TRIGGERED)
	    ::std::cout << "[enabled_triggered]";
	  else if (subsystem_type () == BlockInfo::ACTION)
	    ::std::cout << "[action]";
	  else if (subsystem_type () == BlockInfo::ITERATOR)
	    ::std::cout << "[iterator]";
	}
      ::std::cout << "\n";
      if (upper())
	::std::cout << "  Upper=" << upper()->name() << "\n";
      if (top())
	::std::cout << "  Top=" << top()->name () << "\n";
      for (block_list_const_iterator bl (contain_block ().begin ());
	   bl != contain_block ().end (); bl++)
	{
	  const BlockInfo* cb = *bl;
	  ::std::cout << "  contain: " << cb->block ()->name () << "\n";
	}
      ::std::cout << ::std::endl;
    }


    IOPort::IOPort ()
      : iop_block_tag (NULL), iop_ioport_tag (NULL)
    {
    }

    IOPort::IOPort (block_T* block, ioport_T* ioport)
      : iop_block_tag (block), iop_ioport_tag (ioport)
    {
    }

    void
    IOPort::dump (void) const
    {
      ::std::cout << "block_T " << block_tag()->name() << ":"
		  << ioport_tag()->port() << ::std::endl;
    }

    Reader::Reader ()
    {
    }

    Reader::Reader (const char* xml, bool validation)
    {
      load_xml (xml, validation);
    }

    BlockInfo&
    Reader::add_block_map (block_T* upper, block_T& block)
    {
      ::std::pair< block_map_iterator,
		   bool > x
	= block_map().insert (::std::make_pair (block.name(),
						BlockInfo (&block, upper)));
      return x.first->second;
    }

    IOPort&
    Reader::add_input_map (block_T* block, ioport_T* ioport)
    {
      ioport_map_iterator x
	= r_input_map.insert (::std::make_pair (ioport->port(),
						IOPort (block, ioport)));
      return x->second;
    }

    IOPort&
    Reader::add_output_map (block_T* block, ioport_T* ioport)
    {
      ioport_map_iterator x
	= r_output_map.insert (::std::make_pair (ioport->port(),
						 IOPort (block, ioport)));
      return x->second;
    }

    const IOPort*
    Reader::find_input_port (const ::std::string& block,
			     const ::std::string& port) const
    {
      ioport_map_const_iterator_pair pi = r_input_map.equal_range (port);
      for (ioport_map_const_iterator i = pi.first; i != pi.second; i++)
	{
	  if (i->second.match (block, port))
	    return &i->second;
	}
      return NULL;
    }

    IOPort*
    Reader::find_input_port (const ::std::string& block,
			     const ::std::string& port)
    {
      ioport_map_iterator_pair pi = r_input_map.equal_range (port);
      for (ioport_map_iterator i = pi.first; i != pi.second; i++)
	{
	  if (i->second.match (block, port))
	    return &i->second;
	}
      return NULL;
    }

    const IOPort*
    Reader::find_output_port (const ::std::string& block,
			      const ::std::string& port) const
    {
      ioport_map_const_iterator_pair pi (r_output_map.equal_range (port));
      for (ioport_map_const_iterator i = pi.first; i != pi.second; i++)
	{
	  if (i->second.match (block, port))
	    return &i->second;
	}
      return NULL;
    }

    IOPort*
    Reader::find_output_port (const ::std::string& block,
			      const ::std::string& port)
    {
      ioport_map_iterator_pair pi (r_output_map.equal_range (port));
      for (ioport_map_iterator i = pi.first; i != pi.second; i++)
	{
	  if (i->second.match (block, port))
	    return &i->second;
	}
      return NULL;
    }

    const BlockInfo*
    Reader::find_block (const ::std::string& block) const
    {
      block_map_const_iterator i (block_map().find (block));
      if (i == block_map().end())
	return NULL;
      return &i->second;
    }

    BlockInfo*
    Reader::find_block (const ::std::string& block)
    {
      block_map_iterator i (block_map().find (block));
      if (i == block_map().end())
	return NULL;
      return &i->second;
    }

    const IOPort*
    Reader::find_inport_input (const BlockInfo* port) const
    {
      const BlockInfo* subsys = port->upper_subsystem ();
      if (subsys == NULL)
	return NULL;
      return find_input_port (subsys->block ()->name (),
			      port->block ()->name ());
    }

    IOPort*
    Reader::find_inport_input (const BlockInfo* port)
    {
      BlockInfo* subsys = port->upper_subsystem ();
      if (subsys == NULL)
	return NULL;
      return find_input_port (subsys->block ()->name (),
			      port->block ()->name ());
    }

    const IOPort*
    Reader::find_outport_output (const BlockInfo* port) const
    {
      const BlockInfo* subsys = port->upper_subsystem ();
      if (subsys == NULL)
	return NULL;
      return find_output_port (subsys->block ()->name (),
			       port->block ()->name ());
    }

    IOPort*
    Reader::find_outport_output (BlockInfo* port)
    {
      BlockInfo* subsys = port->upper_subsystem ();
      if (subsys == NULL)
	return NULL;
      return find_output_port (subsys->block ()->name (),
			       port->block ()->name ());
    }

    void
    Reader::process_blocks (BlockInfo* top, block_T* upper,
			    BlockInfo* subsys, blocks_T& blocks)
    {
      BlockInfo* t;

      for (blocks_T::block_iterator bs (blocks.block().begin());
	   bs != blocks.block().end(); bs++)
	{
	  block_T& b = *bs;

	  if (find_block (b.name ()))
	    {
	      ::std::cout << "Warning: Duplicate block in XML: "
			  << b.blocktype () << ":" << b.name ()
			  << ::std::endl;
	      continue;
	    }

	  BlockInfo& binfo = add_block_map (upper, b);

	  binfo.upper_subsystem () = subsys;
	  if (subsys)
	    subsys->lower_block ().push_back (&binfo);

	  if (b.blocktype () == "SubSystem")
	    {
	      binfo.is_subsystem () = true;
	      block_T::type_optional& bt = b.type ();
	      if (bt)
		{
		  if (*bt == "atomic")
		    binfo.subsystem_type () = BlockInfo::ATOMIC;
		  else if (*bt == "enabled")
		    binfo.subsystem_type () = BlockInfo::ENABLED;
		  else if (*bt == "triggered")
		    binfo.subsystem_type () = BlockInfo::TRIGGERED;
		  else if (*bt == "enabled_triggered")
		    binfo.subsystem_type () = BlockInfo::ENABLED_TRIGGERED;
		  else if (*bt == "action")
		    binfo.subsystem_type () = BlockInfo::ACTION;
		  else if (*bt == "iterator")
		    binfo.subsystem_type () = BlockInfo::ITERATOR;
		  else if (*bt == "stateflow")
		    binfo.subsystem_type () = BlockInfo::STATEFLOW;
		}

	      block_T::stateflow_optional& so = b.stateflow ();
	      if (so)
		binfo.subsystem_type () = BlockInfo::STATEFLOW;
	    }
	  else if (b.blocktype () == "S-Function")
	    binfo.is_sfunction () = true;
	  else if (b.blocktype () == "TriggerPort" && subsys != NULL)
	    subsys->trigger_port () = &binfo;
	  else if (b.blocktype () == "EnablePort" && subsys != NULL)
	    subsys->enable_port () = &binfo;
	  else if (b.blocktype () == "ActionPort" && subsys != NULL)
	    subsys->action_port () = &binfo;

	  for (block_T::code_iterator ci (b.code ().begin ());
	       ci != b.code ().end (); ci++)
	    {
	      if (ci->type () == "update")
		{
		  binfo.has_update () = true;
		  break;
		}
	    }

	  if (top)
	    {
	      binfo.top_subsystem () = top;
	      binfo.top () = top->block ();
	      top->contain_block ().push_back (&binfo);
	    }

	  t = top;
	  if (t == NULL
	      && binfo.subsystem_type () == BlockInfo::ITERATOR)
	    t = &binfo;

	  for (block_T::blocks_iterator i (b.blocks().begin ());
	       i != b.blocks ().end (); i++)
	    process_blocks (t, &b, &binfo, *i);
	}
    }


    void
    Reader::process_blocks_complete (void)
    {
      for (block_map_iterator i (block_map ().begin ());
	   i != block_map ().end (); i++)
	{
	  BlockInfo& b = i->second;
	  block_T* bt = b.block ();

	  if (b.id () == 0)
	    b.set_newid ();

	  for (block_T::merged_to_iterator mi (bt->merged_to().begin ());
	       mi != bt->merged_to ().end (); mi++)
	    {
	      block_name_T& m = *mi;
	      BlockInfo* mb = find_block (m.block ());

	      if (mb)
		b.merged_to ().push_back (mb);
	    }

	  for (block_T::merge_block_iterator mi (bt->merge_block().begin ());
	       mi != bt->merge_block ().end (); mi++)
	    {
	      block_name_T& m = *mi;
	      BlockInfo* mb = find_block (m.block ());

	      if (mb)
		b.merge_blocks ().push_back (mb);
	    }

	  for (block_T::bound_to_iterator bi (bt->bound_to().begin ());
	       bi != bt->bound_to ().end (); bi++)
	    {
	      block_name_T& m = *bi;
	      BlockInfo* bb = find_block (m.block ());

	      if (bb)
		b.bound_to ().push_back (bb);
	    }

	  for (block_T::bind_iterator bi (bt->bind().begin ());
	       bi != bt->bind ().end (); bi++)
	    {
	      block_name_T& m = *bi;
	      BlockInfo* bb = find_block (m.block ());

	      if (bb)
		b.bind_blocks ().push_back (bb);
	    }
	}

      // correct `top_subsystem'
      for (block_map_iterator i (block_map ().begin ());
	   i != block_map ().end (); i++)
	{
	  BlockInfo& b = i->second;

	  if (!b.is_subsystem ()
	      || b.top_subsystem () != NULL
	      || !b.contain_block ().empty ()
	      || !b.merged_to ().empty ()
	      || b.lower_block ().empty ()
	      || b.merge_blocks ().empty ())
	    continue;

	  bool all_ok = true;
	  block_list_const_iterator mb (b.merge_blocks ().begin ());
	  block_list_const_iterator me (b.merge_blocks ().end ());

	  for (block_list_const_iterator bi (b.lower_block ().begin ());
	       bi != b.lower_block ().end (); bi++)
	    {
	      if (::std::find (mb, me, *bi) == me)
		{
		  all_ok = false;
		  break;
		}
	    }

	  if (all_ok)
	    {
	      for (block_list_iterator bi (b.lower_block ().begin ());
		   bi != b.lower_block ().end (); bi++)
		process_top_subsystem (&b, *bi);
	    }
	}
    }


    void
    Reader::process_port (blocks_T& blocks)
    {
      for (blocks_T::block_iterator bs (blocks.block().begin());
	   bs != blocks.block().end(); bs++)
	{
	  for (block_T::input_iterator i (bs->input().begin());
	       i != bs->input().end(); i++)
	    add_input_map (&*bs, &*i);

	  for (block_T::output_iterator i (bs->output().begin());
	       i != bs->output().end(); i++)
	    add_output_map (&*bs, &*i);

	  for (block_T::blocks_iterator i (bs->blocks().begin());
	       i != bs->blocks().end(); i++)
	    process_port (*i);
	}
    }


    void
    Reader::process_graph (void)
    {
      for (block_map_iterator i (block_map ().begin ());
	   i != block_map ().end (); i++)
	{
	  BlockInfo& binfo = i->second;

	  const block_T* b = binfo.block ();

	  for (block_T::forward_const_iterator
		 fi (b->forward ().begin ());
	       fi != b->forward ().end (); fi++)
	    {
	      BlockInfo* head = find_block (fi->block());

	      BlockConnect bc (&binfo, head);
	      block_connect_list_T::iterator beg = binfo.forward ().begin ();
	      block_connect_list_T::iterator end = binfo.forward ().end ();

	      block_connect_list_T::iterator bci = ::std::find (beg, end, bc);

	      BlockConnect* xbc;

	      if (bci == end)
		{
		  binfo.forward ().push_back (bc);
		  xbc = &binfo.forward ().back ();
		}
	      else
		xbc = &*bci;

	      for (link_T::var_const_iterator vi (fi->var ().begin ());
		   vi != fi->var ().end (); vi++)
		xbc->var_list().push_back (&*vi);
	    }

	  for (block_T::backward_const_iterator bi (b->backward ().begin ());
	       bi != b->backward ().end (); bi++)
	    {
	      BlockInfo* tail = find_block (bi->block());

	      BlockConnect bc (tail, &binfo);
	      block_connect_list_T::iterator beg = binfo.backward ().begin ();
	      block_connect_list_T::iterator end = binfo.backward ().end ();

	      block_connect_list_T::iterator bci = ::std::find (beg, end, bc);

	      BlockConnect* xbc;

	      if (bci == end)
		{
		  binfo.backward ().push_back (bc);
		  xbc = &binfo.backward ().back ();
		}
	      else
		xbc = &*bci;

	      for (link_T::var_const_iterator vi (bi->var ().begin ());
		   vi != bi->var ().end (); vi++)
		xbc->var_list().push_back (&*vi);
	    }
	}
    }


    void
    Reader::process_all (void)
    {
      process_blocks (NULL, NULL, NULL, *r_blocks);
      process_blocks_complete ();
      process_port (*r_blocks);
      process_graph ();

      size_t size = BlockInfo::max_id () + 1; // id is 1 origin

      block_list_T& bl = block_list ();
      bl.resize (size + 1);

      for (block_map_iterator i (block_map ().begin ());
	   i != block_map ().end (); i++)
	{
	  BlockInfo& b = i->second;
	  if (b.id() <= 0 || size < b.id())
	    ::std::cerr << "Error: BlockInfo id=" << b.id() << ::std::endl;
	  else
	    bl[b.id ()] = &b;
	}
    }

    int
    Reader::load_xml (const char* xml, bool validation)
    {
      try
	{
	  ::std::auto_ptr< blocks_T > blks;

	  if (validation)
	    blks = blocks (xml);
	  else
	    blks = blocks (xml, xml_schema::flags::dont_validate);

	  r_blocks = blks;

	  process_all ();
	}
      catch (const xml_schema::exception& e)
	{
	  ::std::cerr << "Error: " << e << ::std::endl;
	  return -1;
	}
      catch (...)
	{
	  ::std::cerr << "Error: " << xml << ::std::endl;
	  return -1;
	}
      return 0;
    }

    void
    Reader::dump (void) const
    {
      if (block_map().size())
	{
	  ::std::cout << "-- block map --" << ::std::endl;

	  for (block_map_const_iterator i (block_map().begin());
	       i != block_map().end(); i++)
	    i->second.dump();
	}
      if (input_map().size())
	{
	  ::std::cout << "--input map --" << ::std::endl;

	  for (ioport_map_const_iterator i (input_map().begin());
	       i != input_map().end(); i++)
	    i->second.dump();
	}
      if (output_map().size())
	{
	  ::std::cout << "--output map --" << ::std::endl;

	  for (ioport_map_const_iterator i (output_map().begin());
	       i != output_map().end(); i++)
	    i->second.dump();
	}
    }

    int
    Reader::depth_search_for_loop (int s_index, int c_index,
				   int* color, int* route,
				   search_dir dir,
				   bool break_multirate) const
    {
      const block_list_T& bl = block_list ();
      const BlockInfo* c_binfo = bl[c_index];

      color[c_index] = -1;	// Gray

      block_connect_list_T::const_iterator beg;
      block_connect_list_T::const_iterator end;

      if (dir == SEARCH_FORWARD)
	{
	  beg = c_binfo->forward ().begin ();
	  end = c_binfo->forward ().end ();
	}
      else
	{
	  beg = c_binfo->backward ().begin ();
	  end = c_binfo->backward ().end ();
	}

      // search backward (search to Root)
      for (block_connect_list_T::const_iterator i (beg); i != end; i++)
	{
	  const BlockInfo* n_binfo;

	  if (dir == SEARCH_FORWARD)
	    n_binfo = i->head (); // head of edge (forward)
	  else
	    n_binfo = i->tail (); // tail of edge (backward)

	  int n_index = n_binfo->id ();

	  if (s_index == n_index)
	    {
	      route[c_index] = n_index;
	      return 1;
	    }

	  if (break_multirate)
	    {
	      const BlockInfo* c_mss = find_multirate_subsystem (c_binfo);
	      const BlockInfo* n_mss = find_multirate_subsystem (n_binfo);

	      if (c_mss != n_mss)
		continue;	// break multirate
	    }

	  if (color[n_index] == 0) // White
	    {
	      int x = depth_search_for_loop (s_index, n_index, color, route,
					     dir, break_multirate);
	      if (x)
		{
		  route[c_index] = n_index;
		  return x;
		}
	    }

	  color[c_index] = 1;	// Black
	}
      return 0;
    }

    int
    Reader::find_loop (int index, int *route,
		       search_dir dir, bool break_multirate) const
    {
      const block_list_T& bl = block_list ();
      ::std::vector < int > color (bl.size(), 0);
      int x = depth_search_for_loop (index, index,
				     color.data (), route,
				     dir, break_multirate);
#if 0
      if (x)
	{
	  int i = index;
	  const BlockInfo* cur = bl[i];
	  ::std::cout << "----------------\n";
	  ::std::cout << "Found loop: " << i
		      << "(" << cur->block()->name() << ")"
		      << ::std::endl;
	  do
	    {
	      int j = route[i];
	      if (j == -1)
		j = index;

	      const BlockInfo* nxt = bl[j];
	      ::std::cout << "  " << i << "(" << cur->block()->name() << ")"
			  << (dir == SEARCH_FORWARD ? " -> " : " <- ")
			  << j << "(" << nxt->block()->name() << ")"
			  << ::std::endl;
	      i = j;
	      cur = nxt;
	    } while (i != index);
	}
#endif
      return x;
    }

    int
    Reader::find_loop (int index, search_dir dir, bool break_multirate) const
    {
      ::std::vector < int > route (block_list().size(), -1);
      return find_loop (index, route.data (), dir, break_multirate);
    }

    void
    Reader::process_top_subsystem (BlockInfo* top, BlockInfo *binfo)
    {
      binfo->top_subsystem () = top;
      binfo->top () = top->block ();
      top->contain_block ().push_back (binfo);
      for (block_list_iterator bi (binfo->lower_block ().begin ());
	   bi != binfo->lower_block ().end (); bi++)
	process_top_subsystem (top, *bi);
    }
  }
}
