#include <16F877A.h>
#fuses HS,NOWDT,NOPUT,NOLVP,NOPROTECT,BROWNOUT
#use delay(clock=4M) // Ajustar según tu cristal (4M o 20M)

#include "display_max.c"
#include "Estanque.c"

void main() {
   // --- CONFIGURACIÓN DE HARDWARE ---
   setup_adc_ports(NO_ANALOGS); // Pines digitales
   set_tris_e(0b00000111);      // E0, E1, E2 como entradas
   
   max_init(); // Iniciar Pantalla
   
   // Limpiar displays al inicio
   max_send(1, 0); max_send(2, 0); 
   max_send(3, 0); max_send(4, 0);

   // --- BUCLE INFINITO ---
   while(TRUE) {
      
      // 1. Ejecutar Lógica (Todo sucede aquí adentro)
      simular_estanque();

      // 2. Mostrar Nivel (Derecha - Digitos 1 y 2)
      max_send(1, nivel % 10);
      max_send(2, (nivel / 10) % 10);
      
      // 3. Mostrar Tiempo (Izquierda - Digitos 3 y 4)
      max_send(3, tiempo_seg % 10);
      max_send(4, (tiempo_seg / 10) % 10);

      // 4. Base de Tiempo (CRÍTICO: 100ms)
      delay_ms(100); 
   }
}
