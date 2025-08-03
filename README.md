# so_looooong

-[] Add map tile size to data
-[] Restructure data
-[] Replace bool with error_codes

To run it on a newer version of cc, change all CC in minilib Makefile's to '''CC = cc -std=gnu11'''.

First it runs in the main.c
    -> Checks if arguments equals 2
    -> Init the game and check for errors.
    -> activate key and loop hook
    -> free_everything / Quit

In the Init.c
    -> init_mlx
    -> init_assets
    -> init_map
        -> extract map path into data
        -> init exit_pos to -1 -1
        -> init collectibles
            -> count_coullectible
            -> allocate size for collectibles in data
            -> init collectibles.count to 0 in data
        -> init map measurements
            -> get_map_size
            -> allocate size for map.map in data
            -> read from each line and parse accordingly
        -> init visited
        -> get_player_position

    -> check if map is makeable
