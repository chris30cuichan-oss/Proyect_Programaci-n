#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "monitoreo.h"
void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
int validar_entero(int *numero) {
    char linea[100];
    int valido = 0;
    while (!valido) {
        if (fgets(linea, sizeof(linea), stdin) != NULL) {
            linea[strcspn(linea, "\n")] = 0;
            if (strlen(linea) == 0) {
                printf("[ERROR]: No puede dejar el campo vacío. Intente de nuevo: ");
                continue;
            }
            int es_numerico = 1;
            for (int i = 0; linea[i] != '\0'; i++) {
                if (!isdigit((unsigned char)linea[i])) {
                    es_numerico = 0;
                    break;
                }
            }
            if (es_numerico) {
                *numero = atoi(linea);
                valido = 1;
            } else {
                printf("[ERROR]: Entrada inválida. No se permiten letras. Intente de nuevo: ");
            }
        }
    }
    return 1;
}
void validar_texto(char *destino, int longitud_max) {
    char linea[150];
    int valido = 0;
    while (!valido) {
        if (fgets(linea, sizeof(linea), stdin) != NULL) {
            linea[strcspn(linea, "\n")] = 0;
            if (strlen(linea) == 0) {
                printf("[ERROR]: El nombre no puede estar vacío. Intente de nuevo: ");
                continue;
            }
            if ((int)strlen(linea) >= longitud_max) {
                printf("[ERROR]: Texto muy largo. Intente de nuevo: ");
                continue;
            }
            int es_texto_puro = 1;
            for (int i = 0; linea[i] != '\0'; i++) {
                if (!isalpha((unsigned char)linea[i]) && linea[i] != ' ') {
                    es_texto_puro = 0;
                    break;
                }
            }
            if (es_texto_puro) {
                strcpy(destino, linea);
                valido = 1;
            } else {
                printf("[ERROR]: Entrada inválida. No números ni símbolos. Intente de nuevo: ");
            }
        }
    }
}
void inicializar_datos(ZonaUrbana *zonas) {
    char *nombres[] = {"Zona Centro", "Zona Norte Industrial", "Zona Sur Residencial", "Zona Eloy Alfaro", "Zona Tumbaco Valle"};
    for (int i = 0; i < MAX_ZONAS; i++) {
        zonas[i].id = i + 1;
        strcpy(zonas[i].nombre, nombres[i]);
        zonas[i].temperatura = 16.0 + (i * 2.1);
        zonas[i].velocidad_viento = 14.5 - (i * 2.5);
        zonas[i].humedad = 70.0 - (i * 3.0);
        zonas[i].actual.co2 = 380.0 + (i * 25.0);
        zonas[i].actual.so2 = 22.0 + (i * 6.5);
        zonas[i].actual.no2 = 18.0 + (i * 4.0);
        zonas[i].actual.pm25 = 12.0 + (i * 5.5);
        for (int j = 0; j < DIAS_HISTORIAL; j++) {
            zonas[i].historial_pm25[j] = 11.0 + (j * 0.2) + (i * 3.0);
        }
    }
}
void monitorear_actual(const ZonaUrbana *zonas) {
    printf("\n===================================================================\n");
    printf("         ESTADO DE CONTAMINACIÓN ACTUAL DE ZONAS URBANAS\n");
    printf("===================================================================\n");
    for (int i = 0; i < MAX_ZONAS; i++) {
        printf("\n[%d] Zona Urbano-Ambiental: %s\n", zonas[i].id, zonas[i].nombre);
        printf("    - CO2  : %6.2f ppm  (Límite: %.1f)\n", zonas[i].actual.co2, LIMITE_CO2);
        printf("    - SO2  : %6.2f ug/m3 (Límite: %.1f)\n", zonas[i].actual.so2, LIMITE_SO2);
        printf("    - NO2  : %6.2f ug/m3 (Límite: %.1f)\n", zonas[i].actual.no2, LIMITE_NO2);
        printf("    - PM2.5: %6.2f ug/m3 (Límite: %.1f)\n", zonas[i].actual.pm25, LIMITE_PM25);
        if (zonas[i].actual.co2 > LIMITE_CO2 || zonas[i].actual.pm25 > LIMITE_PM25 || 
            zonas[i].actual.so2 > LIMITE_SO2 || zonas[i].actual.no2 > LIMITE_NO2) {
            printf("    STATUS: [ALERTA AMBIENTAL ACTIVA - NIVELES EXCEDIDOS]\n");
            printf("    RECOMENDACIONES DE MITIGACIÓN INTEGRAL:\n");
            printf("    * [SOCIAL/CULTURAL]: Activar de inmediato la restricción vehicular (Pico y Placa ampliado).\n");
            printf("    * [AMBIENTAL/ECONÓMICO]: Suspensión de actividades al aire libre y regulación industrial.\n");
        } else {
            printf("    STATUS: [ESTABLE] - Niveles dentro de los rangos de seguridad recomendados.\n");
        }
    }
}
// <-- NUEVA FUNCIÓN AÑADIDA PARA CUMPLIR LA RÚBRICA -->
void calcular_promedios_historicos(const ZonaUrbana *zonas) {
    printf("\n===================================================================\n");
    printf("       PROMEDIOS HISTÓRICOS (ÚLTIMOS 30 DÍAS) VS LÍMITES OMS\n");
    printf("===================================================================\n");
    for (int i = 0; i < MAX_ZONAS; i++) {
        float suma = 0.0;
        for (int j = 0; j < DIAS_HISTORIAL; j++) {
            suma += zonas[i].historial_pm25[j];
        }
        float promedio = suma / DIAS_HISTORIAL;
        printf("\nZona: %s\n", zonas[i].nombre);
        printf("  -> Promedio PM2.5 (30 días): %.2f ug/m3 | Límite OMS: %.1f ug/m3\n", promedio, LIMITE_PM25);
        if (promedio > LIMITE_PM25) {
            printf("  STATUS: [ALERTA HISTÓRICA] El promedio mensual excede la norma de salud pública.\n");
        } else {
            printf("  STATUS: [NORMAL] Historial dentro de los parámetros de seguridad.\n");
        }
    }
}
void predecir_futuro(const ZonaUrbana *zonas) {
    printf("\n===================================================================\n");
    printf("     SISTEMA DE PREDICCIÓN MATEMÁTICA A 24 HORAS (PROMEDIO PONDERADO)\n");
    printf("===================================================================\n");
    for (int i = 0; i < MAX_ZONAS; i++) {
        float suma_ponderada = 0.0;
        float suma_pesos = 0.0;
        for (int j = 0; j < DIAS_HISTORIAL; j++) {
            float peso = (float)(j + 1); 
            suma_ponderada += zonas[i].historial_pm25[j] * peso;
            suma_pesos += peso;
        }
        float prediccion = suma_ponderada / suma_pesos;
        if (zonas[i].velocidad_viento < 4.0) prediccion *= 1.25;
        if (zonas[i].humedad > 65.0) prediccion *= 1.05;
        printf("\nZona: %s\n", zonas[i].nombre);
        printf("  -> Indicadores climáticos: Viento: %.1f km/h | Humedad: %.1f%%\n", zonas[i].velocidad_viento, zonas[i].humedad);
        printf("  -> PM2.5 Estimado Próximas 24h: %.2f ug/m3 (Límite OMS: %.1f)\n", prediccion, LIMITE_PM25);
        if (prediccion > LIMITE_PM25) {
            printf("  [ALERTA PREVENTIVA EMITIDA]: Riesgo inminente de contingencia.\n");
            printf("  [ACCION SUGERIDA]: Cierre temporal preventivo de calderas en la zona.\n");
        } else {
            printf("  [PREDICCIÓN]: Sin anomalías previstas para el siguiente ciclo diurno.\n");
        }
    }
}
void guardar_reporte(const ZonaUrbana *zonas) {
    FILE *archivo = fopen("reporte_ambientales.txt", "w");
    if (archivo == NULL) {
        printf("\n[ERROR] Falla crítica del sistema operativo al abrir el archivo.\n");
        return;
    }
    fprintf(archivo, "=====================================================================\n");
    fprintf(archivo, "       REPORTE CONSOLIDADO PERSISTENTE - CALIDAD DEL AIRE URBANO     \n");
    fprintf(archivo, "=====================================================================\n\n");
    for (int i = 0; i < MAX_ZONAS; i++) {
        fprintf(archivo, "ID: %d | Zona: %s\n", zonas[i].id, zonas[i].nombre);
        fprintf(archivo, "Concentraciones -> CO2: %.1f ppm | SO2: %.1f ug/m3 | NO2: %.1f ug/m3 | PM2.5: %.1f ug/m3\n",
                zonas[i].actual.co2, zonas[i].actual.so2, zonas[i].actual.no2, zonas[i].actual.pm25);
        fprintf(archivo, "Condiciones Met -> Temp: %.1f C | Viento: %.1f km/h | Humedad: %.1f%%\n",
                zonas[i].temperatura, zonas[i].velocidad_viento, zonas[i].humedad);
        fprintf(archivo, "---------------------------------------------------------------------\n");
    }
    fclose(archivo);
    printf("\n[PERSISTENCIA OK] Datos transferidos exitosamente a 'reporte_ambientales.txt'.\n");
}