/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;         /* border pixel of windows */
static const unsigned int snap      = 16;        /* snap pixel */
static const unsigned int gappih    = 5;         /* horiz inner gap between windows */
static const unsigned int gappiv    = 5;         /* vert inner gap between windows */
static const unsigned int gappoh    = 5;         /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 5;         /* vert outer gap between windows and screen edge */
static       int smartgaps          = 1;         /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;         /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int usealtbar          = 1;        /* 1 means use non-dwm status bar */
static const char *altbarclass      = "Polybar"; /* Alternate bar class name */
static const char *altbarcmd        = "/home/mamba/.config/polybar/bar.sh"; /* Alternate bar launch command */
static const char *fonts[]          = { "Cantarell:size=13", "Iosevka:size=14" };
static const char dmenufont[]       = "Iosevka:size=13";

#include "/home/mamba/.cache/wal/colors-wal-dwm.h"
#include <X11/XF86keysym.h>

/* tagging */
static const char *tags[] = { "", "爵", "", "", "", "", "7", "8" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                            instance         title                 tags mask     isfloating   monitor */
	{ "Pwcalculator",                   NULL,            NULL,                 0,            1,           -1 },
	{ "Qalculate-gtk",                  NULL,            NULL,                 0,            1,           -1 },
	{ "qalculate-qt",                   NULL,            NULL,                 0,            1,           -1 },
	{ "Blueberry.py",                   NULL,            NULL,                 0,            1,           -1 },
	{ "org.gnome.Characters",           NULL,            NULL,                 0,            1,           -1 },
	{ "Pavucontrol",                    NULL,            NULL,                 0,            1,           -1 },
	{ "Com.github.gabutakut.gabutdm",   NULL,            NULL,                 0,            1,           -1 },
	{ "st-256color",                    NULL,            NULL,                 1,            0,           -1 },
	{ "tabbed",                         NULL,            NULL,                 1,            0,           -1 },
	{ "firefox",                        NULL,            NULL,                 1 << 1,       0,           -1 },
	{ "librewolf",                      NULL,            NULL,                 1 << 1,       0,           -1 },
	{ NULL,                             "Places",        NULL,                 1 << 1,       1,           -1 },
	{ "Gedit",                          NULL,            NULL,                 1 << 2,       0,           -1 },
	{ "Emacs",                          NULL,            NULL,                 1 << 2,       0,           -1 },
	{ NULL,                             "libreoffice",   NULL,                 1 << 2,       0,           -1 },
	{ "Gimp",                           NULL,            NULL,                 1 << 2,       0,           -1 },
	{ "Evince",                         NULL,            NULL,                 1 << 2,       0,           -1 },
	{ "calibre",                        NULL,            NULL,                 1 << 2,       0,           -1 },
	{ "Org.gnome.Nautilus",             NULL,            NULL,                 1 << 3,       0,           -1 },
	{ "Geary",                          NULL,            NULL,                 1 << 4,       0,           -1 },
	{ "discord",                        NULL,            NULL,                 1 << 4,       0,           -1 },
	{ "spot",                           NULL,            NULL,                 1 << 4,       0,           -1 },
	{ "Lutris",                         NULL,            NULL,                 1 << 5,       0,           -1 },
	{ "Steam",                          NULL,            NULL,                 1 << 5,       0,           -1 },
	{ "Steam",                          NULL,            "Lista de amigos",    1 << 5,       1,           -1 },
	{ "Steam",                          NULL,            "Steam — Novidades",  1 << 5,       1,           -1 },
	{ "Rare",                           NULL,            NULL,                 1 << 5,       0,           -1 },
	{ "PolyMC",                         NULL,            NULL,                 1 << 5,       1,           -1 },
	{ "steam_proton",                   NULL,            NULL,                 1 << 5,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "类",      tile },    /* first entry is default */
	{ "缾",       NULL },    /* no layout function means floating behavior */
	{ "类",     centeredmaster },
	{ "",        monocle },
	{ "",        spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ ">M>",      centeredfloatingmaster },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]          = { "dmenu_run_i", "-i", "-l", "7", "-g", "1", "-h", "30", "-bw", "5", "-fn", dmenufont, "-sb", sel_bg, "-sf", sel_fg, "-nb", norm_bg, "-nf", norm_fg, "-shb", urg_bg, "-shf", urg_fg, "-p", "Executar:⠀", NULL };
static const char *clipmenucmd[]       = { "clipmenu",    "-i", "-l", "7", "-g", "3", "-h", "30", "-bw", "5", "-fn", dmenufont, "-sb", sel_bg, "-sf", sel_fg, "-nb", norm_bg, "-nf", norm_fg, "-shb", urg_bg, "-shf", urg_fg, NULL };
static const char *termcmd[]           = { "st", NULL };
static const char *tabterm[]           = { "tabbed", "-c", "-r 2", "st", "-w", "''", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,                       spawn,          SHCMD("dmenu_launcher") },
	{ MODKEY|ShiftMask,             XK_Return,                  spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_t,                       spawn,          {.v = tabterm } },
	{ MODKEY,                       XK_v,                       spawn,          SHCMD("dmenu_clip") },

	{ 0,                            XF86XK_AudioStop,           spawn,          SHCMD("playerctl stop") },
	{ 0,                            XF86XK_AudioPrev,           spawn,          SHCMD("playerctl previous") },
	{ 0,                            XF86XK_AudioPlay,           spawn,          SHCMD("playerctl play-pause") },
	{ 0,                            XF86XK_AudioNext,           spawn,          SHCMD("playerctl next") },

	{ 0,                            XF86XK_AudioMute,           spawn,          SHCMD("volume mute") },
	{ 0,                            XF86XK_AudioLowerVolume,    spawn,          SHCMD("volume down") },
	{ ShiftMask,                    XF86XK_AudioLowerVolume,    spawn,          SHCMD("volume down1") },
	{ 0,                            XF86XK_AudioRaiseVolume,    spawn,          SHCMD("volume up") },
	{ ShiftMask,                    XF86XK_AudioRaiseVolume,    spawn,          SHCMD("volume up1") },

	{ MODKEY,                       XK_F1,                      spawn,          SHCMD("volume mute") },
	{ MODKEY,                       XK_F2,                      spawn,          SHCMD("volume down") },
	{ MODKEY|ShiftMask,             XK_F2,                      spawn,          SHCMD("volume down1") },
	{ MODKEY,                       XK_F3,                      spawn,          SHCMD("volume up") },	
	{ MODKEY|ShiftMask,             XK_F3,                      spawn,          SHCMD("volume up1") },	

	{ 0,                            XF86XK_MonBrightnessDown,   spawn,          SHCMD("backlight down") }, //Luminosidade
        { ShiftMask,                    XF86XK_MonBrightnessDown,   spawn,          SHCMD("backlight down1") },
	{ 0,                            XF86XK_MonBrightnessUp,     spawn,          SHCMD("backlight up") },
	{ ShiftMask,                    XF86XK_MonBrightnessUp,     spawn,          SHCMD("backlight up1") },

	{ MODKEY,                       XK_F4,                      spawn,          SHCMD("backlight down") },
        { MODKEY|ShiftMask,             XK_F4,                      spawn,          SHCMD("backlight down1") },	
	{ MODKEY,                       XK_F5,                      spawn,          SHCMD("backlight up") },
	{ MODKEY|ShiftMask,             XK_F5,                      spawn,          SHCMD("backlight up1") },

	{ 0,                            XF86XK_TouchpadToggle,      spawn,          SHCMD("touchpad") }, //Touchpad
	{ MODKEY,                       XK_F6,                      spawn,          SHCMD("touchpad") },

	{ MODKEY,                       XK_j,                       spawn,          SHCMD("playerctl previous") }, //Midia
	{ MODKEY,                       XK_k,                       spawn,          SHCMD("playerctl play-pause") },
	{ MODKEY,                       XK_l,                       spawn,          SHCMD("playerctl next") },

	{ 0,                            XK_Print,                   spawn,          SHCMD("gnome-screenshot -c") }, //captura de tela
	{ ControlMask,                  XK_Print,                   spawn,          SHCMD("gnome-screenshot") },
	{ ShiftMask,                    XK_Print,                   spawn,          SHCMD("gnome-screenshot -c -a") },
	{ ShiftMask|ControlMask,        XK_Print,                   spawn,          SHCMD("gnome-screenshot -a") },
	{ MODKEY,                       XK_Print,                   spawn,          SHCMD("gnome-screenshot -i") },

	{ MODKEY,                       XK_f,                       spawn,          SHCMD("$EXPLORER") }, //Atalhos
	{ MODKEY,                       XK_b,                       spawn,          SHCMD("$BROWSER") },
	{ MODKEY,                       XK_e,                       spawn,          SHCMD("$MAIL") },
	{ MODKEY,                       XK_c,                       spawn,          SHCMD("$CALENDAR") },
	{ MODKEY,                       XK_s,                       spawn,          SHCMD("$PLAYER") },
	{ MODKEY,                       XK_period,                  spawn,          SHCMD("$EMOJIS") },
	{ 0,                            XF86XK_Calculator,          spawn,          SHCMD("$CALCULATOR") },

	{ MODKEY,                       XK_p,                       togglebar,      {0} },
	{ MODKEY,                       XK_Up,                      rotatestack,    {.i = +1 } },
	{ MODKEY,                       XK_Down,                    rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_Right,                   focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Left,                    focusstack,     {.i = -1 } },
	{ Mod1Mask,                     XK_Tab,                     focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Up,                      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Down,                    incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Left,                    setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_Right,                   setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,                  zoom,           {0} },
	{ MODKEY,                       XK_equal,                   incrgaps,       {.i = +1 } },
	{ MODKEY,                       XK_minus,                   incrgaps,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_equal,                   togglegaps,     {0} },
	{ MODKEY|ShiftMask,             XK_minus,                   defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,                     view,           {0} },
	{ MODKEY,                       XK_q,                       killclient,     {0} },
	{ MODKEY,                       XK_u,                       setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_i,                       setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_o,                       setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_space,                   setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_space,                   togglefloating, {0} },
	{ MODKEY,                       XK_0,                       view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                       tag,            {.ui = ~0 } },
	{ MODKEY|ControlMask,           XK_comma,                   focusmon,       {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period,                  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                  tagmon,         {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_q,                       quit,           {0} },
	{ MODKEY|ShiftMask,             XK_q,                       quit,           {1} },
	{ MODKEY|ShiftMask,             XK_l,                       spawn,          SHCMD("loginctl lock-session") },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

