#include <iostream>
#include <fstream>
#include <memory>
#include <deque>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "SimulinkModel.hxx"

using namespace SimulinkModel;
using namespace SimulinkModel::XSD;

typedef ::std::map < const ::std::string, const block_T* > block_map;
typedef block_map::iterator block_map_iterator;
typedef block_map::const_iterator block_map_const_iterator;

typedef ::std::deque < const block_T* > block_stack;
typedef block_stack::const_iterator block_stack_const_iterator;

typedef ::std::vector < const param_T* > sig_list;
typedef sig_list::iterator sig_list_iterator;
typedef sig_list::const_iterator sig_list_const_iterator;

typedef ::std::map < const ::std::string, const void* > var_map;
typedef var_map::const_iterator var_map_const_iterator;
typedef var_map::iterator var_map_iterator;
typedef ::std::pair < var_map_iterator, bool > var_map_res;

class block_attr;
typedef ::std::vector < block_attr* > attr_list;

class block_attr
{
public:
  block_attr (block_attr* u, const block_T* b, bool sb)
    : ba_id (ba_seq++), ba_block (b), ba_ignore (false), ba_subsys (sb),
      ba_upper (u)
  {
  }

  int id (void) const { return ba_id; }
  const block_T* block (void) const { return ba_block; }

  bool ignore (void) const { return ba_ignore; }

  void set_ignore (bool i) { ba_ignore = i; }

  block_attr* upper (void) { return ba_upper; }

  attr_list& lowers (void) { return ba_lowers; }

  const block_stack& merged (void) const { return ba_merged; }
  block_stack& merged (void) { return ba_merged; }

  const var_map& vin (void) const { return ba_vin; }
  var_map& vin (void) { return ba_vin; }

  const var_map& vout (void) const { return ba_vout; }
  var_map& vout (void) { return ba_vout; }

  operator bool() const { return ba_ignore; }

private:

  static int ba_seq;
  const int ba_id;
  const block_T* ba_block;
  bool ba_ignore;
  bool ba_subsys;
  block_attr* ba_upper;
  attr_list ba_lowers;
  block_stack ba_merged;
  var_map ba_vin;
  var_map ba_vout;
};

class attr_map
  : public ::std::map < const block_T*, block_attr >
{
public:
  const block_attr* get (const block_T* b) const
  {
    attr_map::const_iterator i = find (b);
    if (i == end ())
      return NULL;
    return &i->second;
  }

  block_attr* get (const block_T* b)
  {
    attr_map::iterator i = find (b);
    if (i == end ())
      return NULL;
    return &i->second;
  }

  int get_id (const block_T* b) const
  {
    const block_attr* ba = get (b);
    if (ba)
      return ba->id ();
    return -1;
  }

  block_attr& add (block_attr* u, const block_T* b, bool sb)
  {
    ::std::pair < attr_map::iterator, bool >
      x = insert (::std::make_pair (b, block_attr (u, b, sb)));
    return x.first->second;
  }
};

class BLXML
{
public:
  BLXML () {}
  BLXML (::std::istream& is);
  BLXML (::std::auto_ptr < blocks_T> b) : blks (b) {}
  ~BLXML () {}

  int load (::std::istream& is);
  int gencode (::std::ostream& os) const;

  void check_switchcase_if_block (void);
  void check_merged_block (void);
  void merge_inout_vars (void);

  void dump (void) const;

  operator bool () const { return this != NULL && blks.get() != NULL; }

private:

  void add_block_map (block_attr* upper, const blocks_T& bs);

  void gen_param_define (::std::ostream& os,
			 var_map& vin, var_map& vout, var_map& vsig,
			 const block_T& b) const;
  void gen_param_define (::std::ostream& os,
			 var_map& vin, var_map& vout, var_map& vsig,
			 block_stack& stack) const;
  void gen_param_define (::std::ostream& os,
			 var_map& vin, var_map& vout, var_map& vsig,
			 const block_T& b, block_stack& stack) const;

  void gen_param_undefine (::std::ostream& os, const block_T& b) const;
  void gen_param_undefine (::std::ostream& os, block_stack& stack) const;
  void gen_param_undefine (::std::ostream& os, const block_T& b,
			   block_stack& stack) const;

  int find_out_signal (sig_list&, const block_T& b) const;

  void gen_input (::std::ostream& os, int& n,
		  var_map& vin, var_map& vsig, const block_T& b) const;
  void gen_input (::std::ostream& os, int& n,
		  var_map& vin, var_map& vsig, block_stack& stack) const;
  void gen_input (::std::ostream& os, int& n,
		  var_map& vin, var_map& vsig,
		  const block_T& b, block_stack& stack) const;

  void gen_output (::std::ostream& os, int& n,
		   var_map& vout, var_map& vsig, const block_T& b) const;
  void gen_output (::std::ostream& os, int& n,
		   var_map& vout, var_map& vsig, block_stack& stack) const;
  void gen_output (::std::ostream& os, int& n,
		   var_map& vout, var_map& vsig,
		   const block_T& b, block_stack& stack) const;

  int gencode (::std::ostream& os, const block_T& b,
	       const ::std::string& type, const code_T* autovars,
	       block_stack& stack) const;
  int gencode (::std::ostream& os, const blocks_T& bs,
	       const code_T* autovars, block_stack& stack) const;

  void define_states (::std::ostream& os, const block_T& b,
		      sig_list& siglist,
		      const ::std::string& prefix, block_stack& stack) const;
  void undefine_states (::std::ostream& os, const block_T& b,
			sig_list& siglist,
			const ::std::string& prefix, block_stack& stack) const;

  void ignore_mark (block_attr* base, block_attr* cur,
		    block_attr* subsys, int* color);

  void ignore_mark_block (block_attr* base, block_attr* cur);

  void merge_inout_vars (block_attr* base, const block_T* b);

  bool push_dsm (const block_T& b, block_stack& stack) const;

  ::std::auto_ptr < blocks_T > blks;

  block_map blockmap;
  block_map ignore_map;

  block_map datastore_map;

  attr_list attrlist;
  attr_map attrmap;
};

static int verbose = 0;		// TODO

static int gen_function_params = 1;

static int no_validate = 0;

::std::vector < const char * > header_list;

int block_attr::ba_seq = 0;

BLXML::BLXML (::std::istream& is)
{
  load (is);
}

void
BLXML::add_block_map (block_attr* upper, const blocks_T& bs)
{
  for (blocks_T::block_const_iterator i (bs.block ().begin ());
       i != bs.block ().end (); i++)
    {
      const block_T& b = *i;
      blockmap.insert (::std::make_pair (b.name(), &b));

      if (b.blocktype () == "DataStoreMemory")
	{
	  const block_T::DataStoreName_optional& o_dsn = b.DataStoreName ();
	  if (o_dsn)
	    datastore_map.insert (::std::make_pair (*o_dsn, &b));
	}

      block_attr& ba = attrmap.add (upper, &b, b.blocktype () == "SubSystem");
      attrlist.push_back (&ba);

      if (upper)
	upper->lowers ().push_back (&ba);

      for (block_T::blocks_const_iterator j (b.blocks ().begin ());
	   j != b.blocks ().end (); j++)
	add_block_map (&ba, *j);
    }
}

int
BLXML::load (::std::istream& is)
{
  ::std::auto_ptr < blocks_T > b;

  try
    {
      if (no_validate)
	b = blocks (is, xml_schema::flags::dont_validate);
      else
	b = blocks (is);
      add_block_map (NULL, *b);
    }
  catch (const ::xml_schema::error& e)
    {
      ::std::cerr << "Error: " << e << ::std::endl;
      return -1;
    }
  catch (const xercesc::XMLException& e)
    {
      ::std::cerr << "Error: unexpected Xerces-C++ exception" << ::std::endl;
      return -1;
    }
  catch (const ::std::exception& e)
    {
      ::std::cerr << "Error: " << e.what() << ::std::endl;
      return -1;
    }
  catch (...)
    {
      ::std::cerr << "Error" << ::std::endl;
      return -1;
    }

  blks = b;
  return 0;
}

::std::string
c_canonicalname (const ::std::string& in)
{
  ::std::string out;
  char c[in.length() + 1];
  char* d = c;
  for (const char* s = in.c_str(); *s; s++)
    {
      unsigned char u = *s;
      if (isalnum (u) || u == '_')
	*d++ = u;
      else if (u == '-')	// replace `-' to `_', and ignore others.
	*d++ = '_';
    }
  *d = 0;
  return ::std::string (c);
}


int
BLXML::find_out_signal (sig_list& list, const block_T& b) const
{
  const block_attr* ba = attrmap.get (&b);
  if (ba->merged().size ())
    {
      for (block_stack::const_iterator i (ba->merged().begin ());
	   i != ba->merged ().end (); i++)
	find_out_signal (list, **i);
    }

  for (block_T::backward_const_iterator bci (b.backward ().begin ());
       bci != b.backward ().end (); bci++)
    {
      block_map_const_iterator bi = blockmap.find (bci->block());
      const block_T* fb = bi->second;

      for (block_T::signal_const_iterator si (fb->signal ().begin ());
	   si != fb->signal ().end (); si++)
	{
	  const param_T& p = *si;
	  for (block_T::var_const_iterator vci (b.var ().begin ());
	       vci != b.var ().end (); vci++)
	    {
	      const var_T& v = *vci;

	      if (v.name () == p.name ())
		{
		  sig_list_const_iterator x = ::std::find (list.begin (),
							   list.end (),
							   &p);
		  if (x == list.end ())
		    list.push_back (&p);
		  break;
		}
	    }
	}
    }
  return list.size ();
}


void
get_storage (block_stack& stack,
	     int& sig_cnt, int& param_cnt, int& cparam_cnt,
	     int& state_cnt, int& trigger_cnt, int& invariant_cnt,
	     const ::std::string*& sig_storage,
	     const ::std::string*& param_storage,
	     const ::std::string*& cparam_storage,
	     const ::std::string*& state_storage,
	     const ::std::string*& trigger_storage,
	     const ::std::string*& invariant_storage)
{
  sig_cnt = 0;
  param_cnt = 0;
  cparam_cnt = 0;
  state_cnt = 0;
  trigger_cnt = 0;
  invariant_cnt = 0;

  sig_storage = NULL;
  param_storage = NULL;
  cparam_storage = NULL;
  state_storage = NULL;
  trigger_storage = NULL;
  invariant_storage = NULL;

  for (block_stack_const_iterator bi (stack.begin());
       bi != stack.end(); bi++)
    {
      const block_T& sb = **bi;

      if (sb.signal().size())
	{
	  sig_cnt += sb.signal().size();
	  if (sig_storage == NULL)
	    {
	      const param_T& p = *sb.signal().begin();
	      sig_storage = &p.storage();
	    }
	}
      if (sb.param().size())
	{
	  param_cnt += sb.param().size();
	  if (param_storage == NULL)
	    {
	      const param_T& p = *sb.param().begin();
	      param_storage = &p.storage();
	    }
	}
      if (sb.const_param().size())
	{
	  cparam_cnt += sb.const_param().size();
	  if (cparam_storage == NULL)
	    {
	      const param_T& p = *sb.const_param().begin();
	      cparam_storage = &p.storage();
	    }
	}
      if (sb.state().size())
	{
	  state_cnt += sb.state().size();
	  if (state_storage == NULL)
	    {
	      const param_T& p = *sb.state().begin();
	      state_storage = &p.storage();
	    }
	}

      if (sb.trigger_state().size())
	{
	  trigger_cnt += sb.trigger_state().size();
	  if (trigger_storage == NULL)
	    {
	      const param_T& p = *sb.trigger_state().begin();
	      trigger_storage = &p.storage();
	    }
	}

      if (sb.invariant_signal().size())
	{
	  invariant_cnt += sb.invariant_signal().size();
	  if (invariant_storage == NULL)
	    {
	      const param_T& p = *sb.invariant_signal().begin();
	      invariant_storage = &p.storage();
	    }
	}
    }
}

void
output_member (::std::ostream& os, const param_T& p,
	       const ::std::string* a = NULL)
{
  os << "  " << p.type() << " " << p.name ();

  param_T::size_optional s = p.size();
  if (s)
    os << "[" << *s << "]";
  os << ";";
  if (a)
    os << " // " << *a;
  os << "\n";
}

void
output_init_value (::std::ostream& os,
		   const ::std::string& name, const block_T& b)
{
  for (block_T::code_const_iterator ci (b.code().begin());
       ci != b.code().end(); ci++)
    {
      const code_T& cc = *ci;
      if (cc.type() == name)
	{
	  os << cc;
	  break;
	}
    }
}


bool
BLXML::push_dsm (const block_T& b, block_stack& stack) const
{
  const block_T::DataStoreName_optional& o_dsn = b.DataStoreName ();

  if (!o_dsn || b.blocktype () == "DataStoreMemory")
    return false;

  block_map_const_iterator i = datastore_map.find (*o_dsn);
  if (i == datastore_map.end ())
    return false;

  const block_T* dsm = i->second;
  if (dsm == &b)
    return false;

  if (::std::find (stack.begin (), stack.end (), dsm) != stack.end ())
    return false;

  stack.push_front (dsm);
  return true;
}

void
BLXML::define_states (::std::ostream& os, const block_T& b,
		      sig_list& siglist,
		      const ::std::string& prefix, block_stack& stack) const
{
  ::std::string name (prefix + "__" + c_canonicalname (b.name ()));
  int sig_cnt = 0;
  int param_cnt = 0;
  int cparam_cnt = 0;
  int state_cnt = 0;
  int trigger_cnt = 0;
  int invariant_cnt = 0;

  const ::std::string* sig_storage = NULL;
  const ::std::string* param_storage = NULL;
  const ::std::string* cparam_storage = NULL;
  const ::std::string* state_storage = NULL;
  const ::std::string* trigger_storage = NULL;
  const ::std::string* invariant_storage = NULL;

  bool dsm_pushed = push_dsm (b, stack);

  stack.push_front (&b);

  get_storage (stack,
	       sig_cnt, param_cnt, cparam_cnt,
	       state_cnt, trigger_cnt, invariant_cnt,
	       sig_storage, param_storage, cparam_storage,
	       state_storage, trigger_storage, invariant_storage);

  if (siglist.size())
    {
      sig_cnt += siglist.size();

      if (sig_storage == NULL)
	{
	  const param_T* p = siglist.front();
	  sig_storage = &p->storage ();
	}
    }

  // signal & param & state macros
  if (sig_cnt)
    {
      os << "#define " << *sig_storage << " "
	 << name << "__" << *sig_storage << "\n";
      os << "struct {\n";

      var_map smap;

      const ::std::string sigcom ("signal");
      for (sig_list_const_iterator si (siglist.begin ());
	   si != siglist.end (); si++)
	{
	  const param_T* p = *si;
	  var_map_res r = smap.insert (::std::make_pair (p->name(), p));
	  if (r.second)
	    output_member (os, *p, &sigcom);
	}

      for (block_stack_const_iterator bi (stack.begin ());
	   bi != stack.end (); bi++)
	{
	  const block_T& sb = **bi;
	  for (block_T::signal_const_iterator pi (sb.signal().begin());
	       pi != sb.signal().end(); pi++)
	    {
	      const param_T& p = *pi;
	      var_map_res r = smap.insert (::std::make_pair (p.name(), &p));
	      if (r.second)
		output_member (os, *pi);
	    }
	}

      os << "} " << name << "__" << *sig_storage << ";\n\n";
    }

  if (param_cnt)
    {
      os << "#define " << *param_storage << " "
	 << name << "__" << *param_storage << "\n";
      os << "struct {\n";

      var_map smap;

      bool has_initcode = true;
      for (block_stack_const_iterator bi (stack.begin ());
	   bi != stack.end (); bi++)
	{
	  const block_T& sb = **bi;
	  for (block_T::param_const_iterator pi (sb.param().begin());
	       pi != sb.param().end(); pi++)
	    {
	      const param_T& p = *pi;
	      var_map_res r = smap.insert (::std::make_pair (p.name (), &p));
	      if (r.second)
		{
		  output_member (os, p);
		  const param_T::initcode_optional& ic = p.initcode ();
		  if (!ic)
		    has_initcode = false;
		}
	    }
	}

      os << "} " << name << "__" << *param_storage << " = {\n";

      if (has_initcode)
	smap.clear ();
      for (block_stack_const_iterator bi (stack.begin ());
	   bi != stack.end (); bi++)
	{
	  const block_T& sb = **bi;
	  if (has_initcode)
	    {
	      for (block_T::param_const_iterator pi (sb.param().begin());
		   pi != sb.param().end(); pi++)
		{
		  const param_T& p = *pi;
		  var_map_res
		    r = smap.insert (::std::make_pair (p.name (), &p));
		  if (r.second)
		    {
		      const param_T::initcode_optional& ic = p.initcode ();
		      if (ic)
			os << *ic;
		    }
		}
	    }
	  else
	    output_init_value (os, "param", sb);
	}

      os << "};\n\n";
    }

  if (cparam_cnt)
    {
      os << "#define " << *cparam_storage << " "
	     << name << "__" << *cparam_storage << "\n";
      os << "struct {\n";

      var_map smap;

      bool has_initcode = true;
      for (block_stack_const_iterator bi (stack.begin ());
	   bi != stack.end (); bi++)
	{
	  const block_T& sb = **bi;
	  for (block_T::const_param_const_iterator
		 pi (sb.const_param().begin());
	       pi != sb.const_param().end(); pi++)
	    {
	      const param_T& p = *pi;
	      var_map_res r = smap.insert (::std::make_pair (p.name (), &p));
	      if (r.second)
		{
		  output_member (os, p);
		  const param_T::initcode_optional& ic = p.initcode ();
		  if (!ic)
		    has_initcode = false;
		}
	    }
	}

      os << "} " << name << "__" << *cparam_storage << " = {\n";

      if (has_initcode)
	smap.clear ();
      for (block_stack_const_iterator bi (stack.begin ());
	   bi != stack.end (); bi++)
	{
	  const block_T& sb = **bi;
	  if (has_initcode)
	    {
	      for (block_T::const_param_const_iterator
		     pi (sb.const_param().begin());
		   pi != sb.const_param().end(); pi++)
		{
		  const param_T& p = *pi;
		  var_map_res
		    r = smap.insert (::std::make_pair (p.name (), &p));
		  if (r.second)
		    {
		      const param_T::initcode_optional& ic = p.initcode ();
		      if (ic)
			os << *ic;
		    }
		}
	    }
	  else
	    output_init_value (os, "const", sb);
	}

      os << "};\n\n";

    }

  if (state_cnt)
    {
      os << "#define " << *state_storage << " "
	 << name << "__" << *state_storage << "\n";
      os << "struct {\n";

      var_map smap;

      for (block_stack_const_iterator bi (stack.begin ());
	   bi != stack.end (); bi++)
	{
	  const block_T& sb = **bi;

	  for (block_T::state_const_iterator pi (sb.state().begin());
	       pi != sb.state().end(); pi++)
	    {
	      const param_T& p = *pi;
	      var_map_res r = smap.insert (::std::make_pair (p.name (), &p));
	      if (r.second)
		output_member (os, *pi);
	    }
	}

      os << "} " << name << "__" << *state_storage << ";\n\n";
    }

  if (trigger_cnt)
    {
      os << "#define " << *trigger_storage << " "
	 << name << "__" << *trigger_storage << "\n";
      os << "struct {\n";

      var_map smap;

      for (block_stack_const_iterator bi (stack.begin ());
	   bi != stack.end (); bi++)
	{
	  const block_T& sb = **bi;

	  for (block_T::trigger_state_const_iterator
		 pi (sb.trigger_state().begin());
	       pi != sb.trigger_state().end(); pi++)
	    {
	      const param_T& p = *pi;
	      var_map_res r = smap.insert (::std::make_pair (p.name (), &p));
	      if (r.second)
		output_member (os, *pi);
	    }
	}

      os << "} " << name << "__" << *trigger_storage << ";\n\n";
    }

  if (invariant_cnt)
    {
      os << "#define " << *invariant_storage << " "
	 << name << "__" << *invariant_storage << "\n";
      os << "struct {\n";

      var_map smap;

      bool has_initcode = true;
      for (block_stack_const_iterator bi (stack.begin ());
	   bi != stack.end (); bi++)
	{
	  const block_T& sb = **bi;
	  for (block_T::invariant_signal_const_iterator
		 pi (sb.invariant_signal().begin());
	       pi != sb.invariant_signal().end(); pi++)
	    {
	      const param_T& p = *pi;
	      var_map_res r = smap.insert (::std::make_pair (p.name (), &p));
	      if (r.second)
		{
		  output_member (os, p);
		  const param_T::initcode_optional& ic = p.initcode ();
		  if (!ic)
		    has_initcode = false;
		}
	    }
	}

      os << "} " << name << "__" << *invariant_storage << " = {\n";

      if (has_initcode)
	smap.clear ();
      for (block_stack_const_iterator bi (stack.begin ());
	   bi != stack.end (); bi++)
	{
	  const block_T& sb = **bi;
	  if (has_initcode)
	    {
	      for (block_T::invariant_signal_const_iterator
		     pi (sb.invariant_signal().begin());
		   pi != sb.invariant_signal().end(); pi++)
		{
		  const param_T& p = *pi;
		  var_map_res
		    r = smap.insert (::std::make_pair (p.name (), &p));
		  if (r.second)
		    {
		      const param_T::initcode_optional& ic = p.initcode ();
		      if (ic)
			os << *ic;
		    }
		}
	    }
	  else
	    output_init_value (os, "invariant_signal", sb);
	}

      os << "};\n";
    }

  stack.pop_front();

  if (dsm_pushed)
    stack.pop_front ();
}


void
BLXML::undefine_states (::std::ostream& os, const block_T& b,
			sig_list& siglist,
			const ::std::string& prefix, block_stack& stack) const
{
  ::std::string name (prefix + "__" + c_canonicalname (b.name ()));

  int sig_cnt = 0;
  int param_cnt = 0;
  int cparam_cnt = 0;
  int state_cnt = 0;
  int trigger_cnt = 0;
  int invariant_cnt = 0;

  const ::std::string* sig_storage = NULL;
  const ::std::string* param_storage = NULL;
  const ::std::string* cparam_storage = NULL;
  const ::std::string* state_storage = NULL;
  const ::std::string* trigger_storage = NULL;
  const ::std::string* invariant_storage = NULL;

  bool dsm_pushed = push_dsm (b, stack);

  stack.push_front (&b);

  get_storage (stack,
	       sig_cnt, param_cnt, cparam_cnt,
	       state_cnt, trigger_cnt, invariant_cnt,
	       sig_storage, param_storage, cparam_storage,
	       state_storage, trigger_storage, invariant_storage);

  if (siglist.size())
    {
      sig_cnt += siglist.size ();
      if (sig_storage == NULL)
	sig_storage = &siglist.front()->storage ();
    }

  if (sig_cnt)
    os << "#undef " << *sig_storage << "\n";
  if (param_cnt)
    os << "#undef " << *param_storage << "\n";
  if (cparam_cnt)
    os << "#undef " << *cparam_storage << "\n";
  if (state_cnt)
    os << "#undef " << *state_storage << "\n";
  if (trigger_cnt)
    os << "#undef " << *trigger_storage << "\n";
  if (invariant_cnt)
    os << "#undef " << *invariant_storage << "\n";

  stack.pop_front ();

  if (dsm_pushed)
    stack.pop_front ();
}


void
BLXML::gen_param_define (::std::ostream& os,
			 var_map& vin, var_map& vout, var_map& vsig,
			 const block_T& b) const
{
  const block_attr* ba = attrmap.get (&b);

  // variables macros
  for (var_map_const_iterator vi (ba->vin ().begin ());
       vi != ba->vin ().end (); vi++)
    {
      const var_T& v = *static_cast< const var_T* > (vi->second);
      if (vsig.find (v.name()) != vsig.end())
	continue;
      var_map_res r = vin.insert (::std::make_pair (v.name(), &v));
      if (r.second)
	os << "#define " << v.name() << " x__" << v.name() << "\n";
    }

  for (var_map_const_iterator vi (ba->vout ().begin ());
       vi != ba->vout ().end (); vi++)
    {
      const var_T& v = *static_cast< const var_T* > (vi->second);
      if (vsig.find (v.name()) != vsig.end())
	continue;
      var_map_res r = vout.insert (::std::make_pair (v.name(), &v));
      if (r.second)
	{
	  os << "#define ";
	  var_T::size_optional s = v.size ();
	  if (s)
	    os << v.name() << " x__" << v.name() << "\n"; // array
	  else
	    os << v.name() << " (*x__" << v.name() << ")\n";
	}
    }
}


void
BLXML::gen_param_define (::std::ostream& os,
			 var_map& vin, var_map& vout, var_map& vsig,
			 block_stack& stack) const
{
  for (block_stack_const_iterator bi (stack.begin ());
       bi != stack.end (); bi++)
    {
      const block_T& sb = **bi;
      gen_param_define (os, vin, vout, vsig, sb);
    }
}

void
BLXML::gen_param_define (::std::ostream& os,
			 var_map& vin, var_map& vout, var_map& vsig,
			 const block_T& b, block_stack& stack) const
{
  gen_param_define (os, vin, vout, vsig, stack);
  gen_param_define (os, vin, vout, vsig, b);
}


void
BLXML::gen_param_undefine (::std::ostream& os, const block_T& b) const
{
  const block_attr* ba = attrmap.get (&b);

  // variables macros
  for (var_map_const_iterator vi (ba->vin ().begin ());
       vi != ba->vin ().end (); vi++)
    {
      const var_T& v = *static_cast< const var_T* > (vi->second);
      os << "#undef " << v.name() << "\n";
    }

  for (var_map_const_iterator vi (ba->vout ().begin ());
       vi != ba->vout ().end (); vi++)
    {
      const var_T& v = *static_cast< const var_T* > (vi->second);
      os << "#undef " << v.name() << "\n";
    }
}


void
BLXML::gen_param_undefine (::std::ostream& os, block_stack& stack) const
{
  for (block_stack_const_iterator bi (stack.begin ());
       bi != stack.end (); bi++)
    {
      const block_T& sb = **bi;
      gen_param_undefine (os, sb);
    }
}


void
BLXML::gen_param_undefine (::std::ostream& os,
			   const block_T& b, block_stack& stack) const
{
  gen_param_undefine (os, stack);
  gen_param_undefine (os, b);
}


void
BLXML::gen_input (::std::ostream& os, int& n,
		  var_map& vin, var_map& vsig, const block_T& b) const
{
  // input variables
  const block_attr* ba = attrmap.get (&b);
  for (var_map_const_iterator vi (ba->vin ().begin ());
       vi != ba->vin ().end (); vi++)
    {
      const var_T& v = *static_cast < const var_T* > (vi->second);
      if (vsig.find (v.name()) != vsig.end())
	continue;
      var_map_res r = vin.insert (::std::make_pair (v.name(), &v));
      if (r.second)
	{
	  if (n++ > 0)
	    os << ", ";
	  os << v.type() << " x__" << v.name();
	  var_T::size_optional s = v.size();
	  if (s)
	    os << "[" << *s << "]";
	}
    }
}

void
BLXML::gen_input (::std::ostream& os, int& n,
		  var_map& vin, var_map& vsig, block_stack& stack) const
{
  for (block_stack_const_iterator bi (stack.begin ());
       bi != stack.end (); bi++)
    {
      const block_T& sb = **bi;
      gen_input (os, n, vin, vsig, sb);
    }
}


void
BLXML::gen_input (::std::ostream& os, int& n,
		  var_map& vin, var_map& vsig,
		  const block_T& b, block_stack& stack) const
{
  gen_input (os, n, vin, vsig, stack);
  gen_input (os, n, vin, vsig, b);
}


void
BLXML::gen_output (::std::ostream& os, int& n,
		   var_map& vout, var_map& vsig, const block_T& b) const
{
  const block_attr* ba = attrmap.get (&b);

  for (var_map_const_iterator vi (ba->vout ().begin ());
       vi != ba->vout ().end (); vi++)
    {
      const var_T& v = *static_cast < const var_T* > (vi->second);
      if (vsig.find (v.name()) != vsig.end())
	continue;
      var_map_res r = vout.insert (::std::make_pair (v.name(), &v));
      if (r.second)
	{
	  if (n++ > 0)
	    os << ", ";
	  os << v.type() << " ";
	  var_T::size_optional s = v.size();
	  if (!s)
	    os << "*";
	  os << "x__" << v.name();
	  if (s)
	    os << "[" << *s << "]";
	}
    }
}


void
BLXML::gen_output (::std::ostream& os, int& n,
		   var_map& vout, var_map& vsig, block_stack& stack) const
{
  for (block_stack_const_iterator bi (stack.begin ());
       bi != stack.end (); bi++)
    {
      const block_T& sb = **bi;
      gen_output (os, n, vout, vsig, sb);
    }
}


void
BLXML::gen_output (::std::ostream& os, int& n,
		   var_map& vout, var_map& vsig,
		   const block_T& b, block_stack& stack) const
{
  gen_output (os, n, vout, vsig, stack);
  gen_output (os, n, vout, vsig, b);
}


int
BLXML::gencode (::std::ostream& os, const block_T& b,
		const ::std::string& type, const code_T* autovars,
		block_stack& stack) const
{
  const block_attr* ba = attrmap.get (&b);
  if (ba->ignore ())
    {
      os << "/* ignore: --- " << b.name () << " --- */\n";
      return 0;
    }

  size_t npush = 0;

  for (block_stack::const_iterator i (ba->merged().begin ());
       i != ba->merged().end (); i++)
    {
      block_stack::const_iterator x = ::std::find (stack.begin (),
						   stack.end (), *i);
      if (x == stack.end ())
	{
	  stack.push_front (*i);
	  npush++;
	}
    }

  ::std::string name (type + "__" + c_canonicalname (b.name ()));
  int n = 0;

  os << "\n";

  sig_list siglist;

  find_out_signal (siglist, b);

  var_map vsig;

  if (gen_function_params)
    {
      for (sig_list_const_iterator si (siglist.begin ());
	   si != siglist.end (); si++)
	{
	  const param_T* s = *si;
	  vsig.insert (::std::make_pair (s->name(), s));
	}

      for (block_T::signal_const_iterator si (b.signal().begin());
	   si != b.signal().end(); si++)
	{
	  const param_T& s = *si;
	  vsig.insert (::std::make_pair (s.name(), &s));
	}

      // variables macros
      var_map vin;
      var_map vout;
      gen_param_define (os, vin, vout, vsig, b, stack);
      undefine_states (os, b, siglist, type, stack);
      define_states (os, b, siglist, type, stack);

      os << "\n";
    }

  os << "void " << name << "(";

  if (gen_function_params)
    {
      // input variables
      var_map vin;
      gen_input (os, n, vin, vsig, b, stack);

      // output variables;
      var_map vout;
      gen_output (os, n, vout, vsig, b, stack);
    }

  os << ")\n" << "{\n";

  if (autovars)
    {
      os << *autovars;
      os << '\n';
    }

  for (block_T::code_const_iterator ci (b.code ().begin ());
       ci != b.code ().end (); ci++)
    {
      const code_T& c = *ci;
      if (c.type () == type)
	os << c;
    }

  os << "}\n";

  if (gen_function_params)
    {
      undefine_states (os, b, siglist, type, stack);
      gen_param_undefine (os, b, stack);
    }

  while (npush-- > 0)
    stack.pop_front ();

  return 0;
}

int
BLXML::gencode (::std::ostream& os, const blocks_T& bs,
		const code_T* autovars, block_stack& stack) const
{
  for (blocks_T::block_const_iterator bi (bs.block().begin());
       bi != bs.block().end(); bi++)
    {
      const block_T& b = *bi;
      const ::std::string& blocktype = b.blocktype();
      const block_T::type_optional &bt = b.type ();

      bool done_task = false;
      bool done_update = false;
      bool done_init = false;

      bool no_code_block = false;

      if ((blocktype == "SubSystem" && (!bt || *bt != "iterator"))
	  || blocktype == "Inport"
	  || blocktype == "Outport"
	  || blocktype == "EnablePort"
	  || blocktype == "TriggerPort")
	no_code_block = true;

      for (block_T::code_const_iterator ci (b.code().begin());
	   ci != b.code().end(); ci++)
	{
	  const code_T& c = *ci;
	  const ::std::string& type = c.type ();

	  if (type == "task" && done_task == false)
	    {
	      if (no_code_block)
		goto no_code_block_error;
	      else
		{
		  int x = gencode (os, b, type, autovars, stack);
		  if (x)
		    return x;
		}
	      done_task = true;
	    }
	  else if (type == "update" && done_update == false)
	    {
	      if (no_code_block)
		goto no_code_block_error;
	      else
		{
		  int x = gencode (os, b, type, autovars, stack);
		  if (x)
		    return x;
		}
	      done_update = true;
	    }
	  else if (type == "init" && done_init == false)
	    {
	      if (no_code_block)
		{
		no_code_block_error:
		  os << "/* !!! " << blocktype << " " << b.name()
		     << " has some code [" << type << "] */\n";
		}
	      else
		{
		  int x = gencode (os, b, type, autovars, stack);
		  if (x)
		    return x;
		}
	      done_init = true;
	    }
	}

      stack.push_back (&b);

      for (block_T::blocks_const_iterator bsi (b.blocks().begin());
	   bsi != b.blocks().end(); bsi++)
	{
	  const blocks_T& sbs = *bsi;
	  int x = gencode (os, sbs, autovars, stack);
	  if (x)
	    return x;
	}

      stack.pop_back ();
    }

  return 0;
}

static bool
inc_cmp (const ::std::pair < int, const include_T* >& a,
	 const ::std::pair < int, const include_T* >& b)
{
  return a.first < b.first;
}

int
BLXML::gencode (::std::ostream& os) const
{
  const blocks_T& bs = *blks;
  const code_T* autovars = NULL;
  int mark_index = -1;

  ::std::vector < ::std::pair < int, const include_T* > > before_inclist;
  ::std::vector < ::std::pair < int, const include_T* > > after_inclist;

  for (blocks_T::includes_const_iterator ii (bs.includes().begin());
       ii != bs.includes().end (); ii++)
    {
      include_T::mark_optional mark = ii->mark ();
      if (mark)
	{
	  mark_index = ii->index ();
	  break;
	}
    }

  for (blocks_T::includes_const_iterator ii (bs.includes().begin());
       ii != bs.includes().end (); ii++)
    {
      if (mark_index != -1 && ii->index () >= mark_index)
	{
	  if (ii->index () > mark_index)
	    after_inclist.push_back (::std::make_pair (ii->index(), &*ii));
	}
      else
	before_inclist.push_back (::std::make_pair (ii->index(), &*ii));
    }

  ::std::sort (before_inclist.begin (), before_inclist.end (), inc_cmp);
  ::std::sort (after_inclist.begin (), after_inclist.end (), inc_cmp);

  for (::std::vector < ::std::pair < int, const include_T* > >::const_iterator
	 i (before_inclist.begin ()); i != before_inclist.end (); i++)
    {
      os << "#include " << i->second->file () << ::std::endl;
    }

  for (blocks_T::code_const_iterator ci (bs.code().begin());
       ci != bs.code().end(); ci++)
    {
      const code_T& c = *ci;
      if (c.type () == "c_macro")
	os << c << "\n";
    }

  for (blocks_T::code_const_iterator ci (bs.code().begin());
       ci != bs.code().end(); ci++)
    {
      const code_T& c = *ci;
      if (c.type () == "rt-macro")
	os << c << "\n";
    }

  for (blocks_T::code_const_iterator ci (bs.code().begin());
       ci != bs.code().end(); ci++)
    {
      const code_T& c = *ci;
      if (c.type () == "rt-type")
	os << c << "\n";
      if (c.type () == "autovars")
	autovars = &c;
    }

  for (blocks_T::deftype_const_iterator di (bs.deftype().begin());
       di != bs.deftype().end(); di++)
    {
      const object_T& o = *di;

      const object_T::kind_optional& ko = o.kind ();
      const object_T::size_optional& sz = o.size();

      if (ko && (*ko == "param" || *ko == "bsignal" || *ko == "bstate"))
	os << o;
      else
	{
	  os << "typedef " << o.type() << " " << o.name();
	  if (sz)
	    os << "[" << *sz << "]";
	  os << ";\n";
	}
    }

  for (blocks_T::object_const_iterator oi (bs.object().begin());
       oi != bs.object().end(); oi++)
    {
      const object_T& o = *oi;

      const object_T::value_optional& v = o.value();

      os << o.type() << " " << o.name();
      if (v)
	os << " = " << *v;
      os << ";\n";
    }

  for (::std::vector < ::std::pair < int, const include_T* > >::const_iterator
	 i (after_inclist.begin ()); i != after_inclist.end (); i++)
    os << "#include " << i->second->file () << ::std::endl;

  for (::std::vector < const char *>::const_iterator i (header_list.begin ());
       i != header_list.end (); i++)
    os << "#include \"" << *i << "\"\n";

  block_stack stack;

  return gencode (os, bs, autovars, stack);
}

void
BLXML::ignore_mark (block_attr* base, block_attr* cur,
		    block_attr* subsys, int* color)

{
  int id = cur->id ();
  const block_T* b = cur->block ();

  color[id] = -1;

  cur->set_ignore (true);
  base->merged ().push_back (b);

  if (b->blocktype () != "Merge" || subsys != cur->upper ())
    {
      if (b->blocktype () == "SubSystem")
	{
	  for (attr_list::iterator x (cur->lowers ().begin ());
	       x != cur->lowers ().end (); x++)
	    {
	      block_attr* lba = *x;
	      if (color[lba->id ()] == 0)
		ignore_mark (base, lba, subsys, color);
	    }
	}

      for (block_T::forward_const_iterator f (b->forward ().begin ());
	   f != b->forward ().end (); f++)
	{
	  block_map_const_iterator bm = blockmap.find (f->block ());
	  const block_T* fb = bm->second;
	  block_attr* fba = attrmap.get (fb);
	  if (color[fba->id ()] == 0)
	    ignore_mark (base, fba, subsys, color);
	}
    }

  color[cur->id ()] = 1;
}


void
BLXML::check_switchcase_if_block (void)
{
  for (attr_list::iterator i (attrlist.begin ());
       i != attrlist.end (); i++)
    {
      block_attr* ba = *i;
      if (ba->ignore ())
	continue;		// already ignored

      const block_T* b = ba->block ();
      const ::std::string& blocktype = b->blocktype ();

      if (blocktype == "SwitchCase" || blocktype == "If")
	{
	  ::std::vector < int > color (attrlist.size (), 0);
	  ignore_mark (ba, ba, ba->upper (), color.data ());

	  // except self
	  ba->set_ignore (false);
	  ba->merged ().pop_front();
	}
    }
}


void
BLXML::ignore_mark_block (block_attr* base, block_attr* cur)
{
  const block_T* b = cur->block ();

  if (cur->ignore ())
    return;

  cur->set_ignore (true);
  base->merged ().push_back (b);

  if (b->blocktype () == "SubSystem")
    {
      for (attr_list::iterator x (cur->lowers ().begin ());
	   x != cur->lowers ().end (); x++)
	ignore_mark_block (base, *x);
    }
}


void
BLXML::check_merged_block (void)
{
  for (attr_list::iterator i (attrlist.begin ());
       i != attrlist.end (); i++)
    {
      block_attr* ba = *i;
      if (ba->ignore ())
	continue;		// already ignored

      const block_T* b = ba->block ();
      const ::std::string& blocktype = b->blocktype ();
      const block_T::type_optional &bt = b->type ();

      if (blocktype == "SubSystem" && bt && *bt == "iterator")
	{
	  ignore_mark_block (ba, ba);

	  // except self
	  ba->set_ignore (false);
	  ba->merged ().pop_front();
	}

      for (block_T::merge_block_const_iterator mi (b->merge_block ().begin ());
	   mi != b->merge_block ().end (); mi++)
	{
	  block_map_iterator bi = blockmap.find (mi->block ());
	  block_attr* mba = attrmap.get (bi->second);

	  ignore_mark_block (ba, mba);
	}
    }
}


void
BLXML::merge_inout_vars (block_attr* base, const block_T* b)
{
  for (block_T::var_const_iterator vi (b->var ().begin ());
       vi != b->var ().end (); vi++)
    {
      const var_T& v = *vi;
      var_map_iterator xi = base->vin ().find (v.name ());
      if (xi != base->vin ().end ())
	continue;		// already existing in vin
      xi = base->vout ().find (v.name ());
      if (xi != base->vout ().end ())
	{
	  // remove from vout, add to vin
	  base->vout ().erase (xi);
	  base->vin ().insert (::std::make_pair (v.name (), &v));
	  continue;
	}

      if (v.mode () == "extout" || v.mode () == "output")
	base->vout ().insert (::std::make_pair (v.name (), &v));
      else
	base->vin ().insert (::std::make_pair (v.name (), &v));
    }
}


void
BLXML::merge_inout_vars (void)
{
  for (attr_list::iterator i (attrlist.begin ());
       i != attrlist.end (); i++)
    {
      block_attr* ba = *i;
      if (ba->ignore ())
	continue;		// already ignored

      merge_inout_vars (ba, ba->block ());
      for (block_stack::iterator i (ba->merged ().begin ());
	   i != ba->merged ().end (); i++)
	merge_inout_vars (ba, *i);
    }
}


void
BLXML::dump (void) const
{
  // TODO
}

int
main(int argc, char * const *argv)
{
  int c;
  const char *output = NULL;
  const char *input = NULL;
  int x;

  while ((c = getopt (argc, argv, "nvo:NH:")) != -1)
    {
      switch (c)
	{
	case 'v':
	  verbose = 1;
	  break;
	case 'o':
	  output = optarg;
	  break;
	case 'N':
	  gen_function_params = 0;
	  break;
	case 'H':
	  header_list.push_back (optarg);
	  break;
	case 'n':
	  no_validate = 1;
	  break;
	case '?':
	  ::std::cerr << "usage: " << argv[0]
		      << " [-n] [-v] [-o output] [-N] [-H user-header] [BLXML]"
		      << ::std::endl;
	  return 1;
	}
    }

  argv += optind;

  if (*argv)
    input = *argv;

  BLXML blxml;

  if (input)
    {
      ::std::ifstream ifs (input);
      if (!ifs)
	{
	  ::std::cerr << input << ": " << strerror (errno) << ::std::endl;
	  return 1;
	}
      x = blxml.load (ifs);
    }
  else
    x = blxml.load (::std::cin);

  if (x)
    return 1;

  blxml.check_switchcase_if_block ();
  blxml.check_merged_block ();
  blxml.merge_inout_vars ();

  if (output)
    {
      ::std::ofstream ofs (output);
      if (!ofs)
	{
	  ::std::cerr << input << ": " << strerror (errno) << ::std::endl;
	  return 1;
	}
      x = blxml.gencode (ofs);
    }
  else
    {
      x = blxml.gencode (::std::cout);
    }

  if (x)
    return 1;
  return 0;
}
