
#!/bin/sh

# Save pgm and yaml files to src folder
xterm -e "rosrun map_server map_saver -f $(rospack find wall_follower_pkg)/map/personal_map"