#ifndef MONITOREO_H
#define MONITOREO_H
#define MAX_ZONAS 5
#define DIAS_HISTORIAL 30
#define MAX_NOMBRE 50
// Límites Máximos Aceptables (Establecidos bajo referencias de la OMS)
#define LIMITE_CO2 400.0   // ppm
#define LIMITE_SO2 40.0    // ug/m3
#define LIMITE_NO2 25.0    // ug/m3
#define LIMITE_PM25 15.0   // ug/m3
// Estructura para almacenar los niveles de contaminantes
typedef struct {
    float co2;
    float so2;
    float no2;
    float pm25;
} Contaminantes;
// Estructura principal para cada zona urbana
typedef struct {
    int id;
    char nombre[MAX_NOMBRE];
    Contaminantes actual;
    float temperatura;
    float velocidad_viento;
    float humedad;
    float historial_pm25[DIAS_HISTORIAL]; 
} ZonaUrbana;
// Validaciones
void limpiar_buffer();
int validar_entero(int *numero);
void validar_texto(char *destino, int longitud_max);
// Funciones del Sistema
void inicializar_datos(ZonaUrbana *zonas);
void monitorear_actual(const ZonaUrbana *zonas);
void calcular_promedios_historicos(const ZonaUrbana *zonas); // <-- NUEVA FUNCIÓN AGREGADA
void predecir_futuro(const ZonaUrbana *zonas);
void guardar_reporte(const ZonaUrbana *zonas);
#endif