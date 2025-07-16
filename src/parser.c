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

void find_player(char **map, t_player *player)
{
    int y = 0;
    int x;
    
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            if (map[y][x] == 'N' || map[y][x] == 'S' || 
                map[y][x] == 'E' || map[y][x] == 'W')
            {
                player->x = x + 0.5;
                player->y = y + 0.5;
                
                // Establecer dirección según orientación
                if (map[y][x] == 'N') { player->dir_x = 0; player->dir_y = -1; }
                if (map[y][x] == 'S') { player->dir_x = 0; player->dir_y = 1; }
                if (map[y][x] == 'E') { player->dir_x = 1; player->dir_y = 0; }
                if (map[y][x] == 'W') { player->dir_x = -1; player->dir_y = 0; }
                
                // ✅ Correcto: usar 'player' no 'game'
                player->plane_x = -player->dir_y * FOV;
                player->plane_y = player->dir_x * FOV;
                
                //map[y][x] = '0';
                return;
            }
            x++;
        }
        y++;
    }
}
