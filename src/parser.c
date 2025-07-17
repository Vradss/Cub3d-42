#include "cub3D.h"

char **read_map_simple(char *filename)
{
    int fd;
    char *line;
    char **map;
    int i = 0;
    
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        printf("❌ Error: No se puede abrir el archivo\n");
        return (NULL);
    }
    
    // Saltar las 6 primeras líneas (texturas y colores)
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
    {
        free(line);
    }
    else
    {
        printf("❌ No se pudo leer línea vacía\n");
    }
    
    // Leer el mapa
    map = malloc(sizeof(char*) * 10);
    i = 0;
    

    while ((line = get_next_line(fd)))
    {        
        // Eliminar salto de línea
        int len = strlen(line);
        if (len > 0 && line[len-1] == '\n')
            line[len-1] = '\0';
            
        if (strlen(line) > 0)
        {
            map[i] = strdup(line);
            i++;
        }
        free(line);
    }
    map[i] = NULL;
    
    close(fd);
    return (map);
}

// En tu función find_player, asegúrate de inicializar correctamente:
void find_player(char **map, t_player *player)
{
    int i = 0;
    int j;
    
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
                    player->plane_x = 0.66;
                    player->plane_y = 0.0;
                }
                else if (map[i][j] == 'S')
                {
                    player->dir_x = 0.0;
                    player->dir_y = 1.0;
                    player->plane_x = -0.66;
                    player->plane_y = 0.0;
                }
                else if (map[i][j] == 'E')
                {
                    player->dir_x = 1.0;
                    player->dir_y = 0.0;
                    player->plane_x = 0.0;
                    player->plane_y = 0.66;
                }
                else if (map[i][j] == 'W')
                {
                    player->dir_x = -1.0;
                    player->dir_y = 0.0;
                    player->plane_x = 0.0;
                    player->plane_y = -0.66;
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