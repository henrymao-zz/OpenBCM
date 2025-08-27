#ifndef SWITCHDEV_BROADCOM_H
#define SWITCHDEV_BROADCOM_H


int async_obj_switch_create_cb(struct async_object_s *obj);
int async_obj_switch_update_cb(struct async_object_s *obj);
int async_obj_switch_delete_cb(struct async_object_s *obj);

int async_obj_vlan_create_cb(struct async_object_s *obj);
int async_obj_vlan_update_cb(struct async_object_s *obj);
int async_obj_vlan_delete_cb(struct async_object_s *obj);

int async_obj_intf_create_cb(struct async_object_s *obj);
int async_obj_intf_update_cb(struct async_object_s *obj);
int async_obj_intf_delete_cb(struct async_object_s *obj);

int async_obj_l3host_create_cb(struct async_object_s *obj);
int async_obj_l3host_update_cb(struct async_object_s *obj);
int async_obj_l3host_delete_cb(struct async_object_s *obj);

int async_obj_neigh_create_cb(struct async_object_s *obj);
int async_obj_neigh_update_cb(struct async_object_s *obj);
int async_obj_neigh_delete_cb(struct async_object_s *obj);


int async_obj_fib_create_cb(struct async_object_s *obj);
int async_obj_fib_update_cb(struct async_object_s *obj);
int async_obj_fib_delete_cb(struct async_object_s *obj);

#endif
