// display_max.c - Driver para MAX7219
#define MAX_DIN   PIN_B0
#define MAX_CLK   PIN_B1
#define MAX_CS    PIN_B2

void max_pulse_clk(void) {
   output_high(MAX_CLK); delay_us(1); output_low(MAX_CLK);
}

void max_sendByte(int8 data) {
   int i;
   for(i=0; i<8; i++) {
      if(data & 0x80) output_high(MAX_DIN);
      else            output_low(MAX_DIN);
      max_pulse_clk();
      data <<= 1;
   }
}

void max_send(int8 reg, int8 data) {
   output_low(MAX_CS);
   max_sendByte(reg);
   max_sendByte(data);
   output_high(MAX_CS);
}

void max_init(void) {
   output_low(MAX_DIN); output_low(MAX_CLK); output_high(MAX_CS);
   set_tris_b(0b11111000); 
   delay_ms(50);
   max_send(0x0F, 0x00); // Test Off
   max_send(0x0C, 0x01); // Shutdown Off
   max_send(0x0B, 0x03); // Scan Limit 4 digitos
   max_send(0x0A, 0x0F); // Intensidad Max
   max_send(0x09, 0xFF); // Decode Mode BCD (todos)
   // Limpiar pantalla
   max_send(1, 0x0F); max_send(2, 0x0F); max_send(3, 0x0F); max_send(4, 0x0F); 
}
