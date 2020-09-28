short *vga = (short*) 0xB8000;		/* VGA address */

void corn_print(char *string, short color)
{
    int i;
    for (i = 0; i < sizeof(string); i++)
    {
        vga[i+80] = color | string[i];
    }
    vga += (i * 80);
}