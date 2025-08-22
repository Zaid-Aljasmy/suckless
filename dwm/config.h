/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMonoNL NFP:size=13"};
static const char dmenufont[]       = "JetBrainsMonoNL NFP:size=13";
static const char col_gray1[]       = "#1a1b26";
static const char col_gray2[]       = "#32344a";
static const char col_gray3[]       = "#a9b1d6";
static const char col_gray4[]       = "#565f89";
static const char col_cyan[]        = "#9ece6a";
static const char col_blue[]        = "#4d6a8e";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray1, col_blue,  col_blue  },
};

static const char *const autostart[] = {
    "xautolock", "-time", "5", "-locker", "slock", "-notify", "30", "-notifier", "slock will start in 30 seconds", NULL,
    "redshift", "-P", "-O", "5500", NULL,
    "setxkbmap", "-layout", "us,ara", "-option", "grp:alt_space_toggle", NULL,
    "dunst", NULL,
    "brightnessctl", "set", "30%", NULL,
    "xset", "-b", NULL,
    "xinput", "--set-prop", "10", "libinput Accel Speed", "1", NULL,
    "xset", "r", "rate", "200", "40", NULL,
    "nitrogen", "--restore", NULL,
    "slstatus", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       0,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_blue, "-sf", col_gray1, "-p", "Search:", NULL };
static const char *powercmd[] = { "/usr/local/bin/powerdmenu.sh", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

/* volume control */
#include <X11/XF86keysym.h>

static const char *upvol[]   = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL };
static const char *downvol[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL };
static const char *mutevol[] = { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };
static const char *mutemic[] = { "pactl", "set-source-mute", "@DEFAULT_SOURCE@", "toggle", NULL };

/* keyboard layout */
static const char *kbdlayout[]  = { "setxkbmap", "-layout", "us,ara", "-option", "grp:alt_space_toggle", NULL };

/* Redshift */
static const char *redshift_on[]  = { "redshift", "-P", "-O", "5500", NULL };
static const char *redshift_off[] = { "redshift", "-x", NULL };

/* Screenshot */
static const char *screenshotcmd[] = {
    "sh", "-c",
    "scrot ~/Pictures/Screenshots/screenshot_%Y-%m-%d-%H%M%S.png -e 'xclip -selection clipboard -t image/png -i $f && notify-send \"Screenshot saved and copied to clipboard\"'",
    NULL
};

/* ColorPicker */
static const char *colorpickercmd[] = { "sh", "-c", "xcolor | xclip -selection clipboard", NULL };

#include "movestack.c"

static const Key keys[] = {
	/* modifier                     key        function        argument */
    { MODKEY,                       XK_h,      togglebar,      {.ui = 1} },
    { MODKEY|ShiftMask,             XK_h,      togglebar,      {.ui = 0} },
    { MODKEY|ShiftMask,             XK_p,      spawn,          {.v = screenshotcmd } },
    { MODKEY,                       XK_c,      spawn,          {.v = colorpickercmd } },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,             XK_e,      spawn,          {.v = powercmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY,                       XK_Down,   focusstack,     {.i = +1 } },
    { MODKEY,                       XK_Up,     focusstack,     {.i = -1 } },
    { MODKEY,                       XK_Right,  focusstack,     {.i = +1 } },
    { MODKEY,                       XK_Left,   focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_z,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    { MODKEY|Mod1Mask,           XK_Left,  shiftview,      {.i = -1 } },  
    { MODKEY|Mod1Mask,           XK_Right, shiftview,      {.i = +1 } }, 
    { MODKEY|Mod1Mask|ShiftMask, XK_Left,  shifttag,       {.i = -1 } }, 
    { MODKEY|Mod1Mask|ShiftMask, XK_Right, shifttag,       {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    { 0, XF86XK_AudioRaiseVolume,           spawn, {.v = upvol   } },
    { 0, XF86XK_AudioLowerVolume,           spawn, {.v = downvol } },
    { 0, XF86XK_AudioMute,                  spawn, {.v = mutevol } },
    { 0, XF86XK_AudioMicMute,               spawn, {.v = mutemic } },
    { Mod1Mask, XK_space, spawn,                 {.v = kbdlayout } },
    { MODKEY|ShiftMask,             XK_d,   spawn, {.v = redshift_on } },
    { MODKEY|ShiftMask,             XK_x,   spawn, {.v = redshift_off } },
    { Mod1Mask|ShiftMask,             XK_Up,     setmfact,   {.f = -0.05} },
    { Mod1Mask|ShiftMask,             XK_Down,   setmfact,   {.f = +0.05} },
    { Mod1Mask|ShiftMask,             XK_Left,   setmfact,   {.f = -0.05} },
    { Mod1Mask|ShiftMask,             XK_Right,  setmfact,   {.f = +0.05} },
    { MODKEY|ShiftMask,               XK_Up,    movestack,   {.i = -1 } },
    { MODKEY|ShiftMask,               XK_Down,  movestack,   {.i = +1 } },
    { MODKEY|ShiftMask,               XK_Left,  movestack,   {.i = +1 } },
    { MODKEY|ShiftMask,               XK_Right, movestack,   {.i = +1 } }
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
