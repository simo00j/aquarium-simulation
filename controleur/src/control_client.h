int control_client__is_connected(int id);
void control_client__connect(int id);
void control_client__disconnect(int id);
int control_client__set_aquarium_id_named(int aquarium_id, int skt_id);
int control_client__set_aquarium_id(int skt_id);