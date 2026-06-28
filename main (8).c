#include <stdio.h>
#include "monitoreo.h"
#include "validaciones.h"

int main() {
    ZonaUrbana sistema_zonas[MAX_ZONAS];
    int seleccion_menu;
    
    // 1. Carga automática de los primeros 29 días
    inicializar_datos(sistema_zonas);
    
    // 2. Interacción inicial requerida para el día 30
    ingresar_dia_30(sistema_zonas);

    // 3. Flujo normal del sistema
    do {
        printf("\n===================================================================\n");
        printf("     SISTEMA INTEGRAL DE GESTIÓN Y PREDICCIÓN AMBIENTAL (SIGPA-ZU)\n");
        printf("===================================================================\n");
        printf("  1. Monitorear Calidad del Aire Actual e Indicadores OMS\n");
        printf("  2. Calcular y Analizar Promedios Históricos (30 Días) \n"); 
        printf("  3. Ejecutar Algoritmo de Predicción Climática a 24 Horas\n");
        printf("  4. Compilar y Exportar Reporte de Datos a Disco Físico\n");
        printf("  5. Finalizar Operaciones del Sistema\n");
        printf("===================================================================\n");
        printf("Introduzca la opción requerida: ");
        
        validar_entero(&seleccion_menu);
        
        switch (seleccion_menu) {
            case 1:
                monitorear_actual(sistema_zonas);
                break;
            case 2:
                calcular_promedios_historicos(sistema_zonas); 
                break;
            case 3:
                predecir_futuro(sistema_zonas);
                break;
            case 4:
                guardar_reporte(sistema_zonas);
                break;
            case 5:
                printf("\nApagando módulos del SIGPA-ZU de forma segura. Control ambiental finalizado.\n");
                break;
            default:
                printf("\n[AVISO]: Opción fuera de rango numérico (1-5). Intente nuevamente.\n");
        }
    } while (seleccion_menu != 5);
    
    return 0;
}