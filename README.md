# so_looooong

-[] Add map tile size to data
-[] Restructure data
-[] Replace bool with error_codes

To run it on a newer version of cc, change all CC in minilib Makefile's to '''CC = cc -std=gnu11'''.

### In utils_render:
- draw
- load_image
- static draw_moves
- static draw_at_pos

### In utils_question:
- static is_not_in_border
- static is_wall
- is_next_tile_wall
- is_on_exit

### In utils_mix:
- move
- load_all_images
- set_player_pos
- is_same
- get_time_in_ms

### In utils_map_size:
- static get_map_height
- static get_map_width
- get_map_size

### In utils_map_set:
- static parse_map_line
- parse_map
- allocate_for_map

### In utils_map_parse:
- static free_current_map
- static is_another_on_line
- set_player
- set_exit
- set_collectible

### In utils_free:
- static free_images
- static free_map
- static free_mlx
- free_all

### In utils_errors:
- exit_error
- exit_success
- pressed_on_x

### In utils_collectibles:
- static count_collectibles
- add_collectible
- is_all_collectibles_collected
- is_on_collectible
- create_collectibles

### In utils_strings:
- ft_strcmp

### In utils_validity:
- static check_map_at_pos
- static check_is_makeable
- is_makeable

### In init_game:
- static init_mlx
- static init_assets
- static init_map
- static init_data
- init_game

### In event_loops:
- static react_uppon_keycode
- key_hook
- loop_hook

### In main:
- main
