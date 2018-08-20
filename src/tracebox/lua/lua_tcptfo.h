/**
 * Tracebox -- A middlebox detection tool
 *
 *  Copyright 2013-2015 by its authors.
 *  Some rights reserved. See LICENSE, AUTHORS.
 */

#ifndef __LUA_TCPTFO_H_
#define __LUA_TCPTFO_H_

#include "lua_layer.hpp"

struct l_tcptfo_ref : public l_layer_ref<Crafter::TCPOptionFastOpen> {
	using l_layer_ref<Crafter::TCPOptionFastOpen>::l_layer_ref;
	static int l_TCP_TFO(lua_State *l);
	static void register_members(lua_State *l);
	static void register_globals(lua_State *l);
};

#endif
