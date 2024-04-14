#pragma once
#include "main.h"

enum Key_ID
{
    Key_Right,
    Key_Left,
    Key_Up,
    Key_Down,
    Key_Enter,
    Key_A,
    Key_B,
    Key_C,
    Key_D,
    Key_E,
    Key_F,
    Key_G,
    Key_H,
    Key_I,
    Key_J,
    Key_K,
    Key_L,
    Key_M,
    Key_N,
    Key_O,
    Key_P,
    Key_Q,
    Key_R,
    Key_S,
    Key_T,
    Key_U,
    Key_V,
    Key_W,
    Key_X,
    Key_Y,
    Key_Z,
    Key_0,
    Key_1,
    Key_2,
    Key_3,
    Key_4,
    Key_5,
    Key_6,
    Key_7,
    Key_8,
    Key_9,
    Key_num_0,
    Key_num_1,
    Key_num_2,
    Key_num_3,
    Key_num_4,
    Key_num_5,
    Key_num_6,
    Key_num_7,
    Key_num_8,
    Key_num_9,
    Key_LBracket,
    Key_RBracket,
    Key_Quote,
    Key_Colon,
    Key_Comma,
    Key_Period,
    Key_FSlash,
    Key_BSlash,
    Key_Return,
    Key_Minus,
    Key_Plus,
    Key_Multiply,
    Key_Equals,
    Key_Backspace,
    Key_Delete,
    Key_F1,
    Key_F2,
    Key_F3,
    Key_F4,
    Key_F5,
    Key_F6,
    Key_F7,
    Key_F8,
    Key_F9,
    Key_F10,
    Key_F11,
    Key_F12,
    Key_Esc,
    Key_Backquote,
    MouseL,
    MouseR,
    MouseM,
    MouseX1,
    MouseX2,
    MouseFr,
    MouseBk,
    Key_Shift,
    Key_LShift,
    Key_RShift,
    Key_Tab,
    Key_Space,
    Key_Ctrl,
    Key_LCtrl,
    Key_RCtrl,
    Key_Alt,
    Key_LAlt,
    Key_RAlt,
    Key_Pause,
    Key_CapsLock,
    Key_PgUp,
    Key_PgDn,
    Key_Home,
    Key_End,
    Key_Select,
    Key_Print,
    Key_Insert,
    Key_LWIN,
    Key_RWIN,
    Key_NumLock,
    Key_ScrollLock,

    key_COUNT
};

struct Key_Data
{
    bool up;
    bool dn;
    bool on;
};


struct Keys
{
    Key_Data K[key_COUNT];
    bool disconnect = false;

	bool double_click = false;

    v2 Mouse;
    v2 Mouse_rel;
    int ScrollY = 0;
    int scroll_y_diff = 0;
};

enum File_Types
{
	File_Type_Regular,
	File_Type_GIF,
	File_Type_HEIC
};

struct Color
{
    union
    {
        float E[4];
        struct
        {
            float r, g, b, a;
        };
    };
    Color() : E{0, 0, 0, 255} {}
	Color(float r, float g, float b, float a) : E{r, g, b, a} {}
};

struct Vertex
{
    v2 pos;
    v2 uv;
    Color col;
    float z;
};

struct glrect
{
    Vertex V[6];
};

#define RENDER_MODE_VEIWER	0
#define RENDER_MODE_ENCODER	1

struct Shader_Constants_Main { //packed to 16 byte alignment
	f32 aspect_img;
	f32 aspect_wnd;
	f32 scale;
	f32 _padding;

	v2 position;
	i32 pixel_grid;
	f32 true_scale;

	v2 image_dim;
	v2 window;

	v4 rgba_flags;
	
	i32 rotation;
	f32 hue;
	f32 saturation;
	f32 contrast;

	f32 brightness;
	f32 gamma;
	i32 srgb;
	i32 render_mode;

	i32 do_blur;
	u32 blur_samples;
	u32 blur_lod;
	f32 blur_scale;

	v2 crop_a;
	v2 crop_b;
	i32 crop_mode;
};

struct Shader_Constants_BG { //packed to 16 byte alignment
	v2 window;
	f32 size;
	f32 _padding0;

	v3 color1;
	f32 _padding1;

	v3 color2;
	f32 _padding2;

	v4 bg;
};

struct Shader_Constants_Crop { //packed to 16 byte alignment
	v2 window;
	v2 image_pos;

	v2 crop_a;
	v2 crop_b;

	v2 image_dim;

	f32 scale;
};

struct Shader_Constants_Lines { //packed to 16 byte alignment
	v4 color;

	v2 window;
	v2 offset;
};

struct Texture {
	v2                          size;
	ID3D11Texture2D*            d3d_texture;
	ID3D11ShaderResourceView*   srv;
	ID3D11ShaderResourceView*   srv_srgb;
};

enum Encoder_Format {
	Format_Bmp,
	Format_Png,
	//Format_Ico,
	//Format_Jpeg,
	Format_Tiff,
	//Format_Gif,
	//Format_Wmp,
	Format_Dds,
	//Format_Adng,
	Format_Heif,
	//Format_Webp,
	//Format_Raw,

	Format_Count
};

char* encoder_formats_str[] = {
	"BMP",
	"PNG",
	//"Ico",
	//"Jpeg",
	"TIFF",
	//"Gif",
	//"Wmp",
	"DDS",
	//"Adng",
	"HEIF",
	//"Webp",
	//"Raw"
};

struct Image
{
	int w;
	int h;
	int n;
	unsigned char *data;
	int orientation = 0;
	bool has_histo;
	easyexif::EXIFInfo exif_info;
	bool has_exif;
	Texture texture;
	int frac1, frac2;
	float aspect_ratio;
};

struct Shader_Program {
	ID3D11VertexShader 	*vertex_shader;
	ID3D11PixelShader 	*pixel_shader;
	ID3D11InputLayout 	*input_layout; // may be NULL
	ID3D11Buffer 		*constants_buffer; // may be NULL
	size_t				constants_buffer_size;
};

struct Graphics
{
	ID3D11Device1 				*device;
	ID3D11DeviceContext1 		*device_ctx;
	IDXGISwapChain1 			*swap_chain;
	ID3D11Texture2D 			*frame_buffer;
	ID3D11Texture2D 			*depth_buffer;
	ID3D11DepthStencilView 		*depth_buffer_view;
	ID3D11RenderTargetView 		*frame_buffer_view;
	IDXGIFactory               	*factory;
	ID3D11DepthStencilState		*depth_stencil_state;
	ID3D11RasterizerState		*raster_state;
	ID3D11BlendState			*blend_state;
	ID3D11SamplerState			*sampler_linear;
	ID3D11SamplerState			*sampler_nearest;

	iv2							viewport_size;

	Shader_Program 				main_program;
	Shader_Program 				bg_program;
	Shader_Program 				crop_program;
	Shader_Program 				lines_program;

	ID3D11Buffer				*lines_vertex_buffer;

    i32 MAX_GPU = 0;

    Image main_image;
	Texture logo_image;

    float aspect_wnd;
    float aspect_img;
};

enum Alert_Type {
	Alert_Error,
	Alert_Info
};

struct Alert
{
    int timer;
    char string[265];
	Alert_Type type;
};

struct Signals
{
    bool update_pass = false;
    bool init_step_2 = false;
    bool update_orientation_step_2 = false;
    bool update_blending = false;
    bool next_image = false;
    bool reload_file = false;
    bool prev_image = false;
    bool update_truescale = false;
    bool setting_applied = false;
	bool update_scale_ui = false;
};

#define TYPE_UNKNOWN -1
#define TYPE_STB_IMAGE 0
#define TYPE_GIF 1
#define TYPE_WEBP 2
#define TYPE_WEBP_ANIM 3
#define TYPE_MISC 4

struct File_Data
{
    cf_file_t file;
    bool loading = false;
    int type = 0;
    bool failed = false;
    v2 pos = v2();
    float scale = 0;
    int index;
};

enum Cursor_Type {
	Cursor_Type_arrow,
	Cursor_Type_resize_h,
	Cursor_Type_resize_v,
	Cursor_Type_resize_dr,
	Cursor_Type_resize_dl,
	Cursor_Type_text,

	Cursor_Type_count
};

enum UI_Theme_Type {
	UI_Theme_Cactus_Green,
	UI_Theme_Cyber_Blue,
	UI_Theme_Dark_Purple,
	UI_Theme_Crimson_Black,
	UI_Theme_Polar_White,

	UI_Theme_Count,
};
char *themes_str[] {"Cactus Green", "Cyber Blue", "Dark Purple", "Crimson Black", "Ice White"};

struct UI_Theme {
	UI_Color4 bg_main_0;
	UI_Color4 bg_main_1;
	UI_Color4 bg_main_1_d;
	UI_Color4 bg_main_2;
	UI_Color4 bg_main_2_d;
	UI_Color4 bg_main_3;
	UI_Color4 bg_main_4;
	UI_Color4 bg_sub;
	UI_Color4 border_main;
	UI_Color4 separator;
	UI_Color4 text_reg_main;
	UI_Color4 text_reg_main_d;
	UI_Color4 text_reg_light;
	UI_Color4 text_reg_mid;
	UI_Color4 text_error;
	UI_Color4 text_info;

	UI_Color4 text_header_0;
	UI_Color4 text_header_1;
	UI_Color4 text_header_2;

	UI_Color4 text_slider_0;
	UI_Color4 text_slider_1;
	UI_Color4 text_slider_2;

	UI_Color4 pos_btn_0;
	UI_Color4 pos_btn_1;
	UI_Color4 pos_btn_2;

	UI_Color4 neg_btn_0;
	UI_Color4 neg_btn_1;
	UI_Color4 neg_btn_2;
};

struct Global
{
    Graphics graphics;
    Keys keys;
    dynarray <File_Data> files;
    u32 current_file_index;
    CRITICAL_SECTION id_mutex;
    CRITICAL_SECTION mutex;
    CRITICAL_SECTION sort_mutex;
    CRITICAL_SECTION imgui_mutex;
    Signals signals;
    Alert alert;

	IWICImagingFactory* wic_factory = NULL;

    bool keep_menu = false;
    bool loaded = false;
    bool sorting = false;
    bool settings_applied = false;
    bool unicode_font_loaded = false;
    bool imgui_in_frame = false;
    bool show_gui = false;
	bool gui_disabled = false; //inter-frame value, not cross-frame! used by gui functions
	bool gui_disabled_backup = false;

    float scale = 1;
    float truescale = 1;
    float truescale_edit = 1;
    float req_truescale = 1;

	HCURSOR hcursor[Cursor_Type_count];

	bool force_loop;
	i32 force_loop_frames;
	HANDLE loader_event;

	UI_Context *ui;
	UI_Font* ui_font;
	UI_Block* tooltip_block;
	bool ui_want_capture_mouse;
	Dynarray<u32> check_mouse_hashes;
	i32 shapes_texture_id;
	bool ui_mouse_hit_test;
	u32 mouse_dn_hash;
	v4 read_px;

    v2 position = v2(0, 0);
    cf_file_t file;
    v2 pixel_mouse;
    float inspect_colors[4];
	f32 hue = 0;
	f32 saturation = 0;
	f32 contrast = 1;
	f32 brightness = 1;
	f32 gamma;
	bool srgb = 0;
	b32 do_blur;
	i32 blur_samples;
	i32 blur_lod;
	f32 blur_scale;

	int anim_index;
	bool anim_play;
    unsigned char *anim_buffer;
    int *anim_frame_delays;
	Texture anim_texture;
    int anim_frames;
    bool anim_loaded;
    bool settings_visible;
    bool save_as_visible;
    bool exif_data_visible;
    bool dropped_file;
    bool loading_dropped_file;

    int32_t settings_resetpos;
    int32_t settings_resetzoom;
    float settings_movementmag;
    float settings_shiftslowmag;
    bool settings_movementinvert;
    bool settings_autoplayGIFs;
    bool settings_Sort = true;
    bool settings_exif = true;
    bool settings_hide_status_fullscreen = false;
    bool settings_hide_status_with_gui = false;
    bool settings_dont_resize = false;
    bool settings_calculate_histograms = false;
	int32_t settings_selected_theme = UI_Theme_Cactus_Green;

	bool mouse_dragging = false;

	bool crop_mode = false;
	iv2 crop_a;
	iv2 crop_b;

	u64 histo_r[256]; 
	u64 histo_g[256]; 
	u64 histo_b[256]; 
	u64 histo_t[256];
	
	v2 p_histo_r[265];
	v2 p_histo_g[265];
	v2 p_histo_b[265];
	v2 p_histo_t[265];

	bool draw_histo_r = 1;
	bool draw_histo_g = 1;
	bool draw_histo_b = 1;
	bool draw_histo_t = 1;

	u64 histo_max;
	u64 histo_max_edit;
	UI_Block* histo_block;

    bool nearest_filtering = false;
    bool pixel_grid = false;
};

Global global = {0};
Global *G = &global;
