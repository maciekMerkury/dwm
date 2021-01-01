/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 3;        /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int usealtbar          = 0;        /* 1 means use non-dwm status bar */
static const char *altbarclass      = "Polybar"; /* Alternate bar class name */
static const char *alttrayname      = "tray";    /* Polybar tray instance name */
static const char *altbarcmd        = "$HOME/bar.sh"; /* Alternate bar launch command */
static const char *fonts[]          = { "Source Code Pro:size=11" };
static const char dmenufont[]       = "Source Code Pro:size=11";

/* colours */
#include "colours.c"
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_purple[]      = "#87055e";
static const char col_pink[]        = "#6f0587";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
//	[SchemeSel]  = { col_gray4, col_cyan,  col_pink},
//        [SchemeNorm] = { col_gray3,     fgcol, col_gray2 },
        [SchemeSel] = {  fgcol,     bgcol,     hicol2 },
};

static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0" };

static const Rule rules[] = {
    /* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
    /* class                    instance                title           tags mask       isfloating     isterminal       noswallow       monitor */

    { "Alacritty",              NULL,                   NULL,           0,              0,             1,               0,              -1 },
    { "Sxiv",                   "sxiv",                 "sxiv",         0,              0,             0,               0,              -1 },
    { "Brave-browser-beta",     "brave-browser-beta",   NULL,           0 << 8,         0,             0,               0,              -1 },
    { "Zathura",                NULL,                   NULL,           0,              0,             0,               0,              -1 },
    { "jetbrains-goland",       "jetbrains-goland",     NULL,           0,              1,             0,               1,              -1 },
};


/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static int attachbelow = 1;    /* 1 means attach after the currently active window */

#include "layouts.c"
static const Layout layouts[] = {
    /* symbol   arrange function */
    { "[]=",    tile }, /* first entry is default */
    { "><>",    NULL }, /* NULL layout means floating */
    { "[M]",    monocle },
    { "[@]",    spiral },
    { "///",    dwindle },
   /* { "HHH",    grid }, */ /* does not work for some reason; TODO: fix the crash */
    { NULL,     NULL }, /* last entry must be {NULL, NULL} as required by the cycle layouts patch */
};

/* mod keys definitions */
#define MODKEY Mod4Mask
#define TAGKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ TAGKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ TAGKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ TAGKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ TAGKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */

static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated on spawn(), shit breakes if removed */ /*TODO: find a way of removing it */
static const char *dmenucmd[] = { "rofi", "-show", "drun" }; /* it has to be called dmenucmd otherwise dwm and subsiquent patches don't work well and I can't be bothered to change every signle mention to something else */
static const char *rofishowcmd[] = { "rofi", "-show", "run" };

static const char *termcmd[] = { "alacritty", NULL };
static const char *browsercmd[] = { "brave", NULL };
static const char *lockcmd[] = { "xlock", NULL };


/* volume control commands */
static char volumeincrement[] = "10";   /* the valou by which the volume is changed */
static const char *voluppulse[] = { "pamixer", "-i", volumeincrement };
static const char *voldownpulse[] = { "pamixer", "-d", volumeincrement };
static const char *mutetogglepulse[] = { "pamixer", "-t" };

/* key binds */
#include "functions.c"
static Key keys[] = {
    /*modifier                          key             function        argument */
    /* layouts management */
    { MODKEY,                           XK_comma,       cyclelayout,    {.i = -1 } },
    { MODKEY,                           XK_period,      cyclelayout,    {.i = +1 } },
    { MODKEY,                           XK_t,           setlayout,      {.v = &layouts[0] } },
    { MODKEY,                           XK_space,       setlayout,      {0} },
    { MODKEY|ShiftMask,                 XK_space,       togglefloating, {0} }, 
    { MODKEY,                           XK_m,           setlayout,      {.v = &layouts[2] } },
    { MODKEY,                           XK_s,           setlayout,      {.v = &layouts[3] } },
    { MODKEY,                           XK_f,           setlayout,      {.v = &layouts[4] } },
    { MODKEY|ShiftMask,                 XK_f,           setlayout,      {.v = &layouts[5] } },
    //{ MODKEY,                           XK_g,           setlayout,      {.v = &layouts[6] } },
    /* window management */
    { MODKEY,                           XK_j,           focusstack,     {.i = +1 } },
    { MODKEY,                           XK_k,           focusstack,     {.i = -1 } },
    { MODKEY|ShiftMask,                 XK_j,           movestack,      {.i = +1 } },
    { MODKEY|ShiftMask,                 XK_k,           movestack,      {.i = -1 } },
    { MODKEY,                           XK_h,           setmfact,       {.f = -0.05 } },
    { MODKEY,                           XK_l,           setmfact,       {.f = +0.05 } },
    { MODKEY|ShiftMask,                 XK_i,           incnmaster,     {.i = +1 } },
    { MODKEY|ShiftMask,                 XK_d,           incnmaster,     {.i = -1 } },
    { MODKEY|ShiftMask,                 XK_Return,      zoom,           {0} },
    { MODKEY,                           XK_Tab,         view,           {0} },
    { MODKEY,                           XK_q,           killclient,     {0} },
    /* tag management */
    TAGKEYS(                            XK_1,                   0)
    TAGKEYS(                            XK_2,                   1)
    TAGKEYS(                            XK_3,                   2)
    TAGKEYS(                            XK_4,                   3)
    TAGKEYS(                            XK_5,                   4)
    TAGKEYS(                            XK_6,                   5)
    TAGKEYS(                            XK_7,                   6)
    TAGKEYS(                            XK_8,                   7)
    TAGKEYS(                            XK_9,                   8)
    TAGKEYS(                            XK_0,                   9)
    /* dwm management */
    { MODKEY|ControlMask|ShiftMask,     XK_q,           quit,           {0} },
    /* spawning programs */
    { MODKEY,                           XK_Return,      spawn,          {.v = termcmd } },
    { MODKEY,                           XK_d,           spawn,          {.v = rofishowcmd } },
    { MODKEY,                           XK_p,           spawn,          {.v = dmenucmd} },
    { MODKEY,                           XK_b,           spawn,          {.v = browsercmd } },
    { MODKEY|ControlMask,               XK_l,           spawn,          {.v = lockcmd } },
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
