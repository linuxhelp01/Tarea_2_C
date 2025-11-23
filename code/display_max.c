// Pines del MAX7219
#define MAX_DIN   PIN_B0
#define MAX_CLK   PIN_B1
#define MAX_CS    PIN_B2

void max_pulse_clk(void) {
   output_high(MAX_CLK);
   delay_us(1);
   output_low(MAX_CLK);
}

void max_sendByte(unsigned int8 data) {
   int i;
   // Compara el valor ingresado con 0b10000000
   for(i = 0; i < 8; i++) {
      if(data & 0x80) // Si cumple la condicion AND envia un bit alto
         output_high(MAX_DIN);
      else // En caso contrario un bit en bajo
         output_low(MAX_DIN);

      max_pulse_clk(); // Determiando el estado del bit, se confirma mediante un flanco de subida
      
      data <<= 1; //corre el arreglo de bits a la izq 
   }
}

void max_send(unsigned int8 reg, unsigned int8 data) {
   output_low(MAX_CS);
   max_sendByte(reg);
   max_sendByte(data);
   output_high(MAX_CS);
}

void max_init(void) {
   // RB0,RB1,RB2 como salida
   set_tris_b(0b11111000);   // RB0-2 = 0 (salida); RB3-7 entrada
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);

   output_low(MAX_DIN);
   output_low(MAX_CLK);
   output_high(MAX_CS);

   delay_ms(50);

   // Config básica
   max_send(0x0F, 0x00);   // test off
   max_send(0x0C, 0x01);   // salir de shutdown (modo normal)
   max_send(0x0B, 0x03);   // scan limit: muestra 4 digitos
   max_send(0x0A, 0x08);   // intensidad media
   max_send(0x09, 0x0F);   // decode mode: solo DIG0 en BCD (registro 1)
}
