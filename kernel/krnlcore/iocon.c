#include "../include/krnlutils.h"
#include "../mm/tinyalloc.h"

#define KEYBOARD_PORT 0x60

int tab_length = 4;

#define KEY_A 0x1E
#define KEY_B 0x30
#define KEY_C 0x2E
#define KEY_D 0x20
#define KEY_E 0x12
#define KEY_F 0x21
#define KEY_G 0x22
#define KEY_H 0x23
#define KEY_I 0x17
#define KEY_J 0x24
#define KEY_K 0x25
#define KEY_L 0x26
#define KEY_M 0x32
#define KEY_N 0x31
#define KEY_O 0x18
#define KEY_P 0x19
#define KEY_Q 0x10
#define KEY_R 0x13
#define KEY_S 0x1F
#define KEY_T 0x14
#define KEY_U 0x16
#define KEY_V 0x2F
#define KEY_W 0x11
#define KEY_X 0x2D
#define KEY_Y 0x15
#define KEY_Z 0x2C
#define KEY_1 0x02
#define KEY_2 0x03
#define KEY_3 0x04
#define KEY_4 0x05
#define KEY_5 0x06
#define KEY_6 0x07
#define KEY_7 0x08
#define KEY_8 0x09
#define KEY_9 0x0A
#define KEY_0 0x0B
#define KEY_MINUS 0x0C
#define KEY_EQUAL 0x0D
#define KEY_SQUARE_OPEN_BRACKET 0x1A
#define KEY_SQUARE_CLOSE_BRACKET 0x1B
#define KEY_SEMICOLON 0x27
#define KEY_BACKSLASH 0x2B
#define KEY_COMMA 0x33
#define KEY_DOT 0x34
#define KEY_FORESLHASH 0x35
#define KEY_F1 0x3B
#define KEY_F2 0x3C
#define KEY_F3 0x3D
#define KEY_F4 0x3E
#define KEY_F5 0x3F
#define KEY_F6 0x40
#define KEY_F7 0x41
#define KEY_F8 0x42
#define KEY_F9 0x43
#define KEY_F10 0x44
#define KEY_F11 0x85
#define KEY_F12 0x86
#define KEY_BACKSPACE 0x0E
#define KEY_DELETE 0x53
#define KEY_DOWN 0x50
#define KEY_END 0x4F
#define KEY_ENTER 0x1C
#define KEY_ESC 0x01
#define KEY_HOME 0x47
#define KEY_INSERT 0x52
#define KEY_KEYPAD_0 0xD2
#define KEY_KEYPAD_1 0xCF
#define KEY_KEYPAD_2 0xD0
#define KEY_KEYPAD_3 0xD1
#define KEY_KEYPAD_4 0xCB
#define KEY_KEYPAD_5 0x4C
#define KEY_KEYPAD_6 0xCD
#define KEY_KEYPAD_7 0xC7
#define KEY_KEYPAD_8 0xC8
#define KEY_KEYPAD_9 0xC9
#define KEY_KEYPAD_DOT 0xD3
#define KEY_KEYPAD_MUL 0x37
#define KEY_KEYPAD_MINUS 0x4A
#define KEY_KEYPAD_PLUS 0x4E
#define KEY_KEYPAD_DIV 0x35
#define KEY_LEFT 0x4B
#define KEY_PAGE_DOWN 0x51
#define KEY_PAGE_UP 0x49
#define KEY_PRINT_SCREEN 0x37
#define KEY_RIGHT 0x4D
#define KEY_SPACE 0x39
#define KEY_LSHIFT 0x2A
#define KEY_TAB 0x0F
#define KEY_UP 0x48

#define VGA_ADDRESS 0xB8000
#define BUFSIZE 2200

static uint32_t next_line_index = 1;
static uint32_t vga_index;

uint16_t *vga_buffer;

int digit_ascii_codes[10] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};

uint8_t g_fore_color = GREY;
uint8_t g_back_color = BLACK;

uint16_t vga_entry(unsigned char ch, uint8_t fore_color, uint8_t back_color)
{
  uint16_t ax = 0;
  uint8_t ah = 0, al = 0;

  ah = back_color;
  ah <<= 4;
  ah |= fore_color;
  ax = ah;
  ax <<= 8;
  al = ch;
  ax |= al;

  return ax;
}

//clear video buffer array
void clear_vga_buffer(uint16_t **buffer, uint8_t fore_color, uint8_t back_color)
{
  uint32_t i;
  for(i = 0; i < BUFSIZE; i++){
    (*buffer)[i] = vga_entry(NULL, fore_color, back_color);
  }
  next_line_index = 1;
  vga_index = 0;
}

//initialize vga buffer
void init_vga(uint8_t fore_color, uint8_t back_color)
{
  vga_buffer = (uint16_t*)VGA_ADDRESS;
  clear_vga_buffer(&vga_buffer, fore_color, back_color);
  g_fore_color = fore_color;
  g_back_color = back_color;
}

void terminal_scroll()
{
  for (int y = 0; y < 55; y++)
    for (int x = 0; x < 80; x++)
    {
      vga_buffer[y * 55 + x] = vga_buffer[(y + 1) * 80 + x];
    }
  vga_index -= 80;
}

//increase vga_index by width of row(80)

void print_new_line()
{
  if(next_line_index >= 55){
    next_line_index = 0;
    clear_vga_buffer(&vga_buffer, g_fore_color, g_back_color);
  }
  vga_index = 80*next_line_index;
  next_line_index++;
}

//assign ascii character to video buffer
void printkch(char ch)
{
  if (ch == '\n')
    print_new_line();
  else if (ch == '\t')
    for (int i = 0; i < tab_length; i++)
      printkch(' ');
  else if (ch == '\r')
  {
    vga_buffer[vga_index] = vga_entry(' ', g_fore_color, g_back_color);
    vga_index--;
    return;
  }
  else
    vga_buffer[vga_index] = vga_entry(ch, g_fore_color, g_back_color);

  if (vga_index == BUFSIZE)
    terminal_scroll();

  vga_index++;
}

uint32_t digit_count(int num)
{
  uint32_t count = 0;
  if(num == 0)
    return 1;
  while(num > 0){
    count++;
    num = num/10;
  }
  return count;
}

void itoa(int num, char *number)
{
  int dgcount = digit_count(num);
  int index = dgcount - 1;
  char x;
  if(num == 0 && dgcount == 1){
    number[0] = '0';
    number[1] = '\0';
  }else{
    while(num != 0){
      x = num % 10;
      number[index] = x + '0';
      index--;
      num = num / 10;
    }
    number[dgcount] = '\0';
  }
}

//print string by calling print_char
void printk(char *str)
{
  uint32_t index = 0;
  while(str[index]){
    printkch(str[index]);
    index++;
  }
}

//print int by converting it into string
//& then printing string
void printki(int num)
{
  char str_num[digit_count(num)+1];
  itoa(num, str_num);
  printk(str_num);
}

void wait_for_io(uint32_t timer_count)
{
  while (1)
  {
    nop();
    timer_count--;
    if (timer_count <= 0)
      break;
  }
}

int isCap = 0;

char get_ascii_char(uint8_t key_code)
{
  uint8_t ret;
  switch (key_code) 
  {
  case KEY_A: if (isCap) ret = 'A'; else ret = 'a'; break;
  case KEY_B: if (isCap) ret = 'B'; else ret = 'b'; break;
  case KEY_C: if (isCap) ret = 'C'; else ret = 'c'; break;
  case KEY_D: if (isCap) ret = 'D'; else ret = 'd'; break;
  case KEY_E: if (isCap) ret = 'E'; else ret = 'e'; break;
  case KEY_F: if (isCap) ret = 'F'; else ret = 'f'; break;
  case KEY_G: if (isCap) ret = 'G'; else ret = 'g'; break;
  case KEY_H: if (isCap) ret = 'H'; else ret = 'h'; break;
  case KEY_I: if (isCap) ret = 'I'; else ret = 'i'; break;
  case KEY_J: if (isCap) ret = 'J'; else ret = 'j'; break;
  case KEY_K: if (isCap) ret = 'K'; else ret = 'k'; break;
  case KEY_L: if (isCap) ret = 'L'; else ret = 'l'; break;
  case KEY_M: if (isCap) ret = 'M'; else ret = 'm'; break;
  case KEY_N: if (isCap) ret = 'N'; else ret = 'n'; break;
  case KEY_O: if (isCap) ret = 'O'; else ret = 'o'; break;
  case KEY_P: if (isCap) ret = 'P'; else ret = 'p'; break;
  case KEY_Q: if (isCap) ret = 'Q'; else ret = 'q'; break;
  case KEY_R: if (isCap) ret = 'R'; else ret = 'r'; break;
  case KEY_S: if (isCap) ret = 'S'; else ret = 's'; break;
  case KEY_T: if (isCap) ret = 'T'; else ret = 't'; break;
  case KEY_U: if (isCap) ret = 'U'; else ret = 'u'; break;
  case KEY_V: if (isCap) ret = 'V'; else ret = 'v'; break;
  case KEY_W: if (isCap) ret = 'W'; else ret = 'w'; break;
  case KEY_X: if (isCap) ret = 'X'; else ret = 'x'; break;
  case KEY_Y: if (isCap) ret = 'Y'; else ret = 'y'; break;
  case KEY_Z: if (isCap) ret = 'Z'; else ret = 'z'; break;
  case KEY_1: ret = '1'; break;
  case KEY_2: ret = '2'; break;
  case KEY_3: ret = '3'; break;
  case KEY_4: ret = '4'; break;
  case KEY_5: ret = '5'; break;
  case KEY_6: ret = '6'; break;
  case KEY_7: ret = '7'; break;
  case KEY_8: ret = '8'; break;
  case KEY_9: ret = '9'; break;
  case KEY_0: ret = '0'; break;
  case KEY_MINUS: if (isCap) ret = '_'; else ret = '-'; break;
  case KEY_EQUAL: if (isCap) ret = '+'; else ret = '='; break;
  case KEY_SQUARE_OPEN_BRACKET: if (isCap) ret = '{'; else ret = '['; break;
  case KEY_SQUARE_CLOSE_BRACKET: if (isCap) ret = '}'; else ret = ']'; break;
  case KEY_SEMICOLON: if (isCap) ret = ':'; else ret = ';'; break;
  case KEY_BACKSLASH: if (isCap) ret = '|'; else ret = '\\'; break;
  case KEY_COMMA: if (isCap) ret = '<'; else ret = ','; break;
  case KEY_DOT: if (isCap) ret = '>'; else ret = '.'; break;
  case KEY_FORESLHASH: if (isCap) ret = '?'; else ret = '/'; break;
  case KEY_SPACE: ret = ' '; break;
  case KEY_BACKSPACE: ret = '\r'; break;
  case KEY_TAB: ret = '\t'; break;
  case KEY_ENTER: ret = '\n'; break;
  default: return 0;
  }

  return ret;

}

void sleep(uint32_t timer_count)
{
  wait_for_io(timer_count);
}

char get_input_keycode()
{
  char ch = 0;
  while((ch = inb(KEYBOARD_PORT)) != 0){
    if(ch > 0)
      return ch;
  }
  return ch;
}

char getInput()
{
  char ch = 0;
  char keycode = 0;
  char output;

  do
  {
    keycode = get_input_keycode();
    ch = get_ascii_char(keycode);
    output = ch;
    sleep(0x02FFFFFF / 8);
  } while (ch <= 0);
  
  return output;
}

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
  outb(0x3D4, 0x0A);
  outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
  
  outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void disable_cursor()
{
  outb(0x3D5, 0x0A);
  outb(0x3D5, 0x20);
}

void update_cursor(int x, int y)
{
  uint16_t pos = y * 55 + x;

  outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void update_cursor_to_index()
{
  uint16_t pos = vga_index;
  outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}