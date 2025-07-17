#include "cub3D.h"

char **read_map_simple(char *filename)
{
    int fd;
    char *line;
    char **map;
    int i;
    int map_capacity;
    
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        printf("❌ Error: No se puede abrir el archivo\n");
        return (NULL);
    }
    
    // Saltar las 6 primeras líneas (texturas y colores)
    i = 0;
    while (i < 6)
    {
        line = get_next_line(fd);
        if (!line)
        {
            printf("❌ Error: get_next_line devolvió NULL en línea %d\n", i);
            close(fd);
            return (NULL);
        }
        free(line);
        i++;
    }
    
    // Saltar línea vacía
    line = get_next_line(fd);
    if (line)
        free(line);
    
    // Inicializar array dinámico para el mapa
    map_capacity = 20;  // Capacidad inicial más realista
    map = malloc(sizeof(char*) * map_capacity);
    if (!map)
    {
        printf("❌ Error: malloc falló para map\n");
        close(fd);
        return (NULL);
    }
    
    // Leer el mapa línea por línea
    i = 0;
    while ((line = get_next_line(fd)))
    {
        // Verificar si necesitamos más espacio
        if (i >= map_capacity - 1)  // -1 para dejar espacio para NULL
        {
            map_capacity *= 2;
            char **temp = realloc(map, sizeof(char*) * map_capacity);
            if (!temp)
            {
                printf("❌ Error: realloc falló\n");
                free(line);
                // Liberar memoria ya asignada
                while (i > 0)
                {
                    i--;
                    free(map[i]);
                }
                free(map);
                close(fd);
                return (NULL);
            }
            map = temp;
        }
        
        // Eliminar salto de línea
        int len = strlen(line);
        if (len > 0 && line[len-1] == '\n')
            line[len-1] = '\0';
            
        // Solo agregar líneas no vacías
        if (strlen(line) > 0)
        {
            map[i] = strdup(line);
            if (!map[i])  // Verificar que strdup funcionó
            {
                printf("❌ Error: strdup falló\n");
                free(line);
                // Liberar memoria ya asignada
                while (i > 0)
                {
                    i--;
                    free(map[i]);
                }
                free(map);
                close(fd);
                return (NULL);
            }
            i++;
        }
        free(line);
    }
    
    // Terminar el array con NULL
    map[i] = NULL;
    
    close(fd);
    return (map);
}

// Función find_player corregida
void find_player(char **map, t_player *player)
{
    int i = 0;
    int j;
    
    // Verificar que map no sea NULL
    if (!map)
        return;
    
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'N' || map[i][j] == 'S' || 
                map[i][j] == 'E' || map[i][j] == 'W')
            {
                player->x = (double)j + 0.5;
                player->y = (double)i + 0.5;
                
                // Inicializar dirección según orientación
                if (map[i][j] == 'N')
                {
                    player->dir_x = 0.0;
                    player->dir_y = -1.0;
                    player->plane_x = FOV;
                    player->plane_y = 0.0;
                }
                else if (map[i][j] == 'S')
                {
                    player->dir_x = 0.0;
                    player->dir_y = 1.0;
                    player->plane_x = -FOV;
                    player->plane_y = 0.0;
                }
                else if (map[i][j] == 'E')
                {
                    player->dir_x = 1.0;
                    player->dir_y = 0.0;
                    player->plane_x = 0.0;
                    player->plane_y = FOV;
                }
                else if (map[i][j] == 'W')
                {
                    player->dir_x = -1.0;
                    player->dir_y = 0.0;
                    player->plane_x = 0.0;
                    player->plane_y = -FOV;
                }
                
                // Reemplazar jugador con espacio vacío
                map[i][j] = '0';
                return;
            }
            j++;
        }
        i++;
    }
}