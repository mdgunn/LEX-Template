/********************************************************************
*		Copyright (c) 2014-2015, reepblue. All rights reserved.		*
*                                                                   *
*		This product contains software technology licensed from     *
*				 Leadwerks Software. All Rights Reserved.           *
********************************************************************/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "lua-gluecode.h"
#include "string.h"

#include "tolua++.h"

// Classes
#include "App.h"

/* function to release collected object via destructor */
#ifdef __cplusplus
static int tolua_collect_App(lua_State* tolua_S)
{
	App* self = (App*)tolua_tousertype(tolua_S, 1, 0);
	Mtolua_delete(self);
	return 0;
}
#endif

/* function to register type */
static void tolua_reg_types(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, LUA_APP_CLASS);
}

/* method: new of class App */
#ifndef TOLUA_DISABLE_tolua_luacom_App_new00
static int tolua_luacom_App_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertable(tolua_S, 1, LUA_APP_CLASS, 0, &tolua_err) ||
		!tolua_isstring(tolua_S, 2, 0, &tolua_err) ||
		!tolua_isstring(tolua_S, 3, 0, &tolua_err) ||
		!tolua_isnoobj(tolua_S, 4, &tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const string wintitle = ((const string)tolua_tostring(tolua_S, 2, 0));
		const string newmap = ((const string)tolua_tostring(tolua_S, 3, 0));
		{
			App* tolua_ret = (App*)Mtolua_new((App)(wintitle,newmap));
			tolua_pushusertype(tolua_S, (void*)tolua_ret, LUA_APP_CLASS);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror :
	tolua_error(tolua_S, "#ferror in function 'new'.", &tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class App */
#ifndef TOLUA_DISABLE_tolua_luacom_App_delete00
static int tolua_luacom_App_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S, 1, LUA_APP_CLASS, 0, &tolua_err) ||
		!tolua_isnoobj(tolua_S, 2, &tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		App* self = (App*)tolua_tousertype(tolua_S, 1, 0);
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(tolua_S, "invalid 'self' in function 'delete'", NULL);
#endif
		Mtolua_delete(self);
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror :
	tolua_error(tolua_S, "#ferror in function 'delete'.", &tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: App::Loop of class App */
#ifndef TOLUA_DISABLE_tolua_luacom_App_App__Loop00
static int tolua_luacom_App_App__Loop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S, 1, LUA_APP_CLASS, 0, &tolua_err) ||
		!tolua_isnoobj(tolua_S, 2, &tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		App* self = (App*)tolua_tousertype(tolua_S, 1, 0);
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(tolua_S, "invalid 'self' in function 'App::Loop'", NULL);
#endif
		{
			bool tolua_ret = (bool)self->App::Loop();
			tolua_pushboolean(tolua_S, (bool)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror :
	tolua_error(tolua_S, "#ferror in function 'App__Loop'.", &tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: App::SetBackgroundMap of class App */
#ifndef TOLUA_DISABLE_tolua_luacom_App_SetBackgroundMap00
static int tolua_luacom_App_App__SetBackgroundMap00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S, 1, LUA_APP_CLASS, 0, &tolua_err) ||
		!tolua_isstring(tolua_S, 2, 0, &tolua_err) ||
		!tolua_isnoobj(tolua_S, 3, &tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		App* self = (App*)tolua_tousertype(tolua_S, 1, 0);
		const string newmap = ((const string)tolua_tostring(tolua_S, 2, 0));
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(tolua_S, "invalid 'self' in function 'App::SetBackgroundMap'", NULL);
#endif
		{
			bool tolua_ret = (bool)self->App::SetBackgroundMap(newmap);
			tolua_pushboolean(tolua_S, (bool)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
	tolua_lerror :
				 tolua_error(tolua_S, "#ferror in function 'App__SetBackgroundMap'.", &tolua_err);
				 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: App::SetBackgroundMap of class App */
#ifndef TOLUA_DISABLE_tolua_luacom_App_SetStartMap00
static int tolua_luacom_App_App__SetStartMap00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S, 1, LUA_APP_CLASS, 0, &tolua_err) ||
		!tolua_isstring(tolua_S, 2, 0, &tolua_err) ||
		!tolua_isnoobj(tolua_S, 3, &tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		App* self = (App*)tolua_tousertype(tolua_S, 1, 0);
		const string newmap = ((const string)tolua_tostring(tolua_S, 2, 0));
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(tolua_S, "invalid 'self' in function 'App::SetStartMap'", NULL);
#endif
		{
			bool tolua_ret = (bool)self->App::SetStartMap(newmap);
			tolua_pushboolean(tolua_S, (bool)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
	tolua_lerror :
				 tolua_error(tolua_S, "#ferror in function 'App__SetStartMap'.", &tolua_err);
				 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: App::Loadmap of class App */
#ifndef TOLUA_DISABLE_tolua_luacom_App_LoadMap00
static int tolua_luacom_App_App__LoadMap00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S, 1, LUA_APP_CLASS, 0, &tolua_err) ||
		!tolua_isstring(tolua_S, 2, 0, &tolua_err) ||
		!tolua_isnoobj(tolua_S, 3, &tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		App* self = (App*)tolua_tousertype(tolua_S, 1, 0);
		const string newmap = ((const string)tolua_tostring(tolua_S, 2, 0));
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(tolua_S, "invalid 'self' in function 'App::LoadMap'", NULL);
#endif
		{
			bool tolua_ret = (bool)self->App::LoadMap(newmap);
			tolua_pushboolean(tolua_S, (bool)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror :
	tolua_error(tolua_S, "#ferror in function 'App__LoadMap'.", &tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: App::LoadSaveFile of class App */
#ifndef TOLUA_DISABLE_tolua_luacom_App_LoadSaveFile00
static int tolua_luacom_App_App__LoadSaveFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S, 1, LUA_APP_CLASS, 0, &tolua_err) ||
		!tolua_isnoobj(tolua_S, 2, &tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		App* self = (App*)tolua_tousertype(tolua_S, 1, 0);
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(tolua_S, "invalid 'self' in function 'App::LoadSaveFile'", NULL);
#endif
		{
			bool tolua_ret = (bool)self->App::LoadSaveFile();
			tolua_pushboolean(tolua_S, (bool)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
	tolua_lerror :
				 tolua_error(tolua_S, "#ferror in function 'App__LoadSaveFile'.", &tolua_err);
				 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: App::LoadSaveFile of class App */
#ifndef TOLUA_DISABLE_tolua_luacom_App_SaveFile00
static int tolua_luacom_App_App__SaveFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S, 1, LUA_APP_CLASS, 0, &tolua_err) ||
		!tolua_isnoobj(tolua_S, 2, &tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		App* self = (App*)tolua_tousertype(tolua_S, 1, 0);
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(tolua_S, "invalid 'self' in function 'App::SaveFile'", NULL);
#endif
		{
			bool tolua_ret = (bool)self->App::SaveFile();
			tolua_pushboolean(tolua_S, (bool)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
	tolua_lerror :
				 tolua_error(tolua_S, "#ferror in function 'App__SaveFile'.", &tolua_err);
				 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: App::Connected of class App */
#ifndef TOLUA_DISABLE_tolua_luacom_App_Connected00
static int tolua_luacom_App_App__Connected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S, 1, LUA_APP_CLASS, 0, &tolua_err) ||
		!tolua_isnoobj(tolua_S, 2, &tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		App* self = (App*)tolua_tousertype(tolua_S, 1, 0);
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(tolua_S, "invalid 'self' in function 'App::Connected'", NULL);
#endif
		{
			bool tolua_ret = (bool)self->App::Connected();
			tolua_pushboolean(tolua_S, (bool)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror :
	tolua_error(tolua_S, "#ferror in function 'App__Connected'.", &tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: App::Pause of class App */
#ifndef TOLUA_DISABLE_tolua_luacom_App_Pause00
static int tolua_luacom_App_App__Pause00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S, 1, LUA_APP_CLASS, 0, &tolua_err) ||
		!tolua_isnoobj(tolua_S, 2, &tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		App* self = (App*)tolua_tousertype(tolua_S, 1, 0);
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(tolua_S, "invalid 'self' in function 'App::Pause'", NULL);
#endif
		{
			bool tolua_ret = (bool)self->App::Pause();
			tolua_pushboolean(tolua_S, (bool)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror :
	tolua_error(tolua_S, "#ferror in function 'App__Pause'.", &tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: App::IsDevMode of class App */
#ifndef TOLUA_DISABLE_tolua_luacom_App_IsDevMode00
static int tolua_luacom_App_App__IsDevMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S, 1, LUA_APP_CLASS, 0, &tolua_err) ||
		!tolua_isnoobj(tolua_S, 2, &tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		App* self = (App*)tolua_tousertype(tolua_S, 1, 0);
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(tolua_S, "invalid 'self' in function 'App::IsDevMode'", NULL);
#endif
		{
			bool tolua_ret = (bool)self->App::IsDevMode();
			tolua_pushboolean(tolua_S, (bool)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror :
	tolua_error(tolua_S, "#ferror in function 'App__IsDevMode'.", &tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: App::InMenu of class App */
#define TOLUA_DISABLE_tolua_luacom_App_InMenu00
#ifndef TOLUA_DISABLE_tolua_luacom_App_InMenu00
static int tolua_luacom_App_App__InMenu00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S, 1, LUA_APP_CLASS, 0, &tolua_err) ||
		!tolua_isnoobj(tolua_S, 2, &tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		App* self = (App*)tolua_tousertype(tolua_S, 1, 0);
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(tolua_S, "invalid 'self' in function 'App::InMenu'", NULL);
#endif
		{
			bool tolua_ret = (bool)self->App::InMenu();
			tolua_pushboolean(tolua_S, (bool)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror :
	tolua_error(tolua_S, "#ferror in function 'App__InMenu'.", &tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: App::DrawStats of class App */
#ifndef TOLUA_DISABLE_tolua_luacom_App_App__DrawStats00
static int tolua_luacom_App_App__DrawStats00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S, 1, LUA_APP_CLASS, 0, &tolua_err) ||
		!tolua_isboolean(tolua_S, 2, 0, &tolua_err) ||
		!tolua_isnoobj(tolua_S, 3, &tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		App* self = (App*)tolua_tousertype(tolua_S, 1, 0);
		const bool draw = ((const bool)tolua_toboolean(tolua_S, 2, 0));
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(tolua_S, "invalid 'self' in function 'App::DrawStats'", NULL);
#endif
		{
			bool tolua_ret = (bool)self->App::DrawStats(draw);
			tolua_pushboolean(tolua_S, (bool)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror :
	tolua_error(tolua_S, "#ferror in function 'App__DrawStats'.", &tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: App::GetMultisample of class App */
#define TOLUA_DISABLE_tolua_luacom_App_App__GetMultisample00
#ifndef TOLUA_DISABLE_tolua_luacom_App_App__GetMultisample00
static int tolua_luacom_App_App__GetMultisample00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S, 1, LUA_APP_CLASS, 0, &tolua_err) ||
		//!tolua_isvalue(tolua_S, 2, 0, &tolua_err) ||
		!tolua_isnoobj(tolua_S, 2, &tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		App* self = (App*)tolua_tousertype(tolua_S, 1, 0);
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(tolua_S, "invalid 'self' in function 'App::GetMultisample'", NULL);
#endif
		{
			//bool tolua_ret = (bool)self->App::GetMultisample();
			//tolua_pushboolean(tolua_S, (bool)tolua_ret);

			//lua_pushstring(tolua_S, self->App::GetMultisample());
			lua_pushfstring(tolua_S, self->App::GetMultisample());
				/*
			int tolua_ret = (int)self->App::GetMultisample();
			tolua_pushvalue(tolua_S, (int)tolua_ret);
			*/

		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror :
	tolua_error(tolua_S, "#ferror in function 'App__GetMultisample'.", &tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: App::Disconnect of class App */
#ifndef TOLUA_DISABLE_tolua_luacom_App_OpenContext00
static int tolua_luacom_App_App__OpenContext00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S, 1, LUA_APP_CLASS, 0, &tolua_err) ||
		!tolua_isnoobj(tolua_S, 2, &tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		App* self = (App*)tolua_tousertype(tolua_S, 1, 0);
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(tolua_S, "invalid 'self' in function 'App::OpenContext'", NULL);
#endif
		{
			bool tolua_ret = (bool)self->App::OpenContext();
			tolua_pushboolean(tolua_S, (bool)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror :
	tolua_error(tolua_S, "#ferror in function 'App__OpenContext'.", &tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: App::Disconnect of class App */
#ifndef TOLUA_DISABLE_tolua_luacom_App_CloseContext00
static int tolua_luacom_App_App__CloseContext00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S, 1, LUA_APP_CLASS, 0, &tolua_err) ||
		!tolua_isnoobj(tolua_S, 2, &tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		App* self = (App*)tolua_tousertype(tolua_S, 1, 0);
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(tolua_S, "invalid 'self' in function 'App::CloseContext'", NULL);
#endif
		{
			bool tolua_ret = (bool)self->App::CloseContext();
			tolua_pushboolean(tolua_S, (bool)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror :
	tolua_error(tolua_S, "#ferror in function 'App__CloseContext'.", &tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: App::Disconnect of class App */
#ifndef TOLUA_DISABLE_tolua_luacom_App_Disconnect00
static int tolua_luacom_App_App__Disconnect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S, 1, LUA_APP_CLASS, 0, &tolua_err) ||
		!tolua_isnoobj(tolua_S, 2, &tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		App* self = (App*)tolua_tousertype(tolua_S, 1, 0);
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(tolua_S, "invalid 'self' in function 'App::Disconnect'", NULL);
#endif
		{
			bool tolua_ret = (bool)self->App::Disconnect();
			tolua_pushboolean(tolua_S, (bool)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror :
	tolua_error(tolua_S, "#ferror in function 'App__Disconnect'.", &tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: App::Quit of class App */
#ifndef TOLUA_DISABLE_tolua_luacom_App_Quit00
static int tolua_luacom_App_App__Quit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S, 1, LUA_APP_CLASS, 0, &tolua_err) ||
		!tolua_isnoobj(tolua_S, 2, &tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		App* self = (App*)tolua_tousertype(tolua_S, 1, 0);
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(tolua_S, "invalid 'self' in function 'App::Quit'", NULL);
#endif
		{
			bool tolua_ret = (bool)self->App::Quit();
			tolua_pushboolean(tolua_S, (bool)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror :
	tolua_error(tolua_S, "#ferror in function 'App__Quit'.", &tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_luacom_open(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	tolua_reg_types(tolua_S);
	tolua_module(tolua_S, NULL, 0);
	tolua_beginmodule(tolua_S, NULL);
#ifdef __cplusplus
	tolua_cclass(tolua_S, LUA_APP_CLASS, LUA_APP_CLASS, "", tolua_collect_App);
#else
	tolua_cclass(tolua_S, LUA_APP_CLASS, LUA_APP_CLASS, "", NULL);
#endif

	tolua_beginmodule(tolua_S, LUA_APP_CLASS);
		tolua_function(tolua_S, "Create", tolua_luacom_App_new00);
		tolua_function(tolua_S, "Loop", tolua_luacom_App_App__Loop00);
		tolua_function(tolua_S, "SetBackgroundMap", tolua_luacom_App_App__SetBackgroundMap00);
		tolua_function(tolua_S, "SetStartMap", tolua_luacom_App_App__SetStartMap00);
		tolua_function(tolua_S, "LoadMap", tolua_luacom_App_App__LoadMap00);
		tolua_function(tolua_S, "LoadSaveFile", tolua_luacom_App_App__LoadSaveFile00);
		tolua_function(tolua_S, "SaveFile", tolua_luacom_App_App__SaveFile00);
		tolua_function(tolua_S, "Connected", tolua_luacom_App_App__Connected00);
		tolua_function(tolua_S, "Pause", tolua_luacom_App_App__Pause00);
		tolua_function(tolua_S, "IsDevMode", tolua_luacom_App_App__IsDevMode00);
		tolua_function(tolua_S, "DrawStats", tolua_luacom_App_App__DrawStats00);
		tolua_function(tolua_S, "OpenContext", tolua_luacom_App_App__OpenContext00);
		tolua_function(tolua_S, "CloseContext", tolua_luacom_App_App__CloseContext00);
		tolua_function(tolua_S, "Disconnect", tolua_luacom_App_App__Disconnect00);
		tolua_function(tolua_S, "Quit", tolua_luacom_App_App__Quit00);
	tolua_endmodule(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
TOLUA_API int luaopen_luacom(lua_State* tolua_S) {
	return tolua_luacom_open(tolua_S);
};
#endif
