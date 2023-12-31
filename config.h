/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "URWGothic-Demi:size=11" };
static const char dmenufont[]       = "URWGothic-Demi:size=11";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#f0fff0";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#006400";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "", "", "", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "gimp",     NULL,       NULL,       0,            1,           -1 },
 	{ "steam",	NULL,	NULL,	1 << 1,	0,	-1 },
	{ "firefox",  NULL,       NULL,       1 << 0,       0,          -1 },
	{ "discord",  NULL,	NULL,	1 << 2, 0, -1 },
	{ "xscreensaver", NULL, NULL, 1 << 7, 0, -1 },
	{ "vbox",	NULL,	NULL,	1 << 3, 0, -1 }
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "cool-retro-term", NULL };
static const char *firefox[]  =  { "firefox", NULL };
static const char *discord[]  = { "discord", NULL };
static const char *steam[]  = { "steam", NULL };
static const char *pavucontrol[]  = { "pavucontrol", NULL };
static const char *wps[] = { "wps", NULL };
static const char *ymp[] = { "ymp", NULL };
static const char *obs[] = { "obs", NULL };
static const char *dscr[] = { "deepin-screen-recorder", NULL };
static const char *dclc[] = { "deepin-calculator", NULL };
static const char *gimp[] = { "gimp", NULL };
static const char *vbox[] = { "virtualbox", NULL };
static const char *code[] = { "code", NULL };
static const char *fm[] = { "nemo", NULL };
static const char *cisco[] = { "packettracer", NULL };
static const char *bt[] = { "blueman-manager", NULL };
static const char *top[] = {"cool-retro-term", "-e", "btop" };
/* f binds */
static const char *pulsel[] = { "pactl", "set-sink-volume", "0", "-5%", NULL };
static const char *pulser[] = { "pactl", "set-sink-volume", "0", "+5%", NULL };
static const char *pulsem[] = { "pactl", "set-sink-mute", "0", "toggle", NULL };
static const char *settings[] = { "cool-retro-term", "-e", "nvim", "$SETTINGS" };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_a,	   spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
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
	{ MODKEY|ControlMask,		XK_o,	  spawn,	{.v = wps } },
	{ MODKEY|ControlMask,		XK_f,	   spawn,	{.v = firefox } },
	{ MODKEY|ControlMask,		XK_d,	  spawn,	{.v = discord } },
	{ MODKEY|ControlMask,		XK_s,	  spawn,	{.v = steam } },
	{ MODKEY|ControlMask,		XK_v,	  spawn,	{.v = pavucontrol } },			
	{ MODKEY|ControlMask,		XK_z,	  spawn,	{.v = obs } },
	{ MODKEY|ControlMask,		XK_y,	  spawn,	{.v = ymp } },
	{ MODKEY|ControlMask,		XK_x,	  spawn,	{.v = dscr } },
	{ MODKEY|ControlMask,		XK_c,	  spawn,	{.v = dclc } },
	{ MODKEY|ControlMask,		XK_g,	  spawn,	{.v = gimp } },
	{ MODKEY|ControlMask,		XK_w,	  spawn,	{.v = vbox } },
	{ MODKEY|ControlMask,		XK_b,	  spawn,	{.v = code } },
	{ MODKEY,			XK_e,	  spawn,	{.v = fm } },
	{ MODKEY|ControlMask,		XK_p,	  spawn,	{.v = cisco } },
	{ MODKEY|ShiftMask,		XK_b,	  spawn,	{.v = bt } },
	{ MODKEY|ShiftMask,	XK_Escape, spawn,	{.v = top } },
	/* f keys */
	{ 0,	0x1008ff11,	spawn,	{.v = pulsel } },
	{ 0,	0x1008ff13,	spawn,	{.v = pulser } },
	{ 0,	0x1008ff12,	spawn,	{.v = pulsem } },
	{ 0,	0x1008ff81,	spawn,	{.v = settings } },
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

