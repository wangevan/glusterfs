/*
  Copyright (c) 2008-2012 Red Hat, Inc. <http://www.redhat.com>
  This file is part of GlusterFS.

  This file is licensed to you under your choice of the GNU Lesser
  General Public License, version 3 or any later version (LGPLv3 or
  later), or the GNU General Public License, version 2 (GPLv2), in all
  cases as published by the Free Software Foundation.
*/

#ifndef _GLUSTERD_HA_H_
#define _GLUSTERD_HA_H_

#ifndef _CONFIG_H
#define _CONFIG_H
#include "config.h"
#endif

#include <pthread.h>
#include "uuid.h"

#include "glusterfs.h"
#include "xlator.h"
#include "run.h"
#include "logging.h"
#include "call-stub.h"
#include "fd.h"
#include "byte-order.h"
#include "glusterd.h"
#include "rpcsvc.h"

typedef enum glusterd_store_ver_ac_{
        GLUSTERD_VOLINFO_VER_AC_NONE = 0,
        GLUSTERD_VOLINFO_VER_AC_INCREMENT = 1,
        GLUSTERD_VOLINFO_VER_AC_DECREMENT = 2,
} glusterd_volinfo_ver_ac_t;


#define GLUSTERD_STORE_UUID_KEY           "UUID"

#define GLUSTERD_STORE_KEY_VOL_TYPE       "type"
#define GLUSTERD_STORE_KEY_VOL_COUNT      "count"
#define GLUSTERD_STORE_KEY_VOL_STATUS     "status"
#define GLUSTERD_STORE_KEY_VOL_PORT       "port"
#define GLUSTERD_STORE_KEY_VOL_SUB_COUNT  "sub_count"
#define GLUSTERD_STORE_KEY_VOL_STRIPE_CNT  "stripe_count"
#define GLUSTERD_STORE_KEY_VOL_REPLICA_CNT "replica_count"
#define GLUSTERD_STORE_KEY_VOL_BRICK      "brick"
#define GLUSTERD_STORE_KEY_VOL_VERSION    "version"
#define GLUSTERD_STORE_KEY_VOL_TRANSPORT  "transport-type"
#define GLUSTERD_STORE_KEY_VOL_ID         "volume-id"
#define GLUSTERD_STORE_KEY_RB_STATUS      "rb_status"
#define GLUSTERD_STORE_KEY_RB_SRC_BRICK   "rb_src"
#define GLUSTERD_STORE_KEY_RB_DST_BRICK   "rb_dst"
#define GLUSTERD_STORE_KEY_VOL_DEFRAG     "rebalance_status"
#define GLUSTERD_STORE_KEY_USERNAME       "username"
#define GLUSTERD_STORE_KEY_PASSWORD       "password"

#define GLUSTERD_STORE_KEY_BRICK_HOSTNAME "hostname"
#define GLUSTERD_STORE_KEY_BRICK_PATH     "path"
#define GLUSTERD_STORE_KEY_BRICK_PORT     "listen-port"
#define GLUSTERD_STORE_KEY_BRICK_RDMA_PORT "rdma.listen-port"
#define GLUSTERD_STORE_KEY_BRICK_DECOMMISSIONED "decommissioned"

#define GLUSTERD_STORE_KEY_PEER_UUID      "uuid"
#define GLUSTERD_STORE_KEY_PEER_HOSTNAME  "hostname"
#define GLUSTERD_STORE_KEY_PEER_STATE     "state"

#define glusterd_for_each_entry(entry, dir) \
        do {\
                entry = NULL;\
                if (dir) {\
                        entry = readdir (dir);\
                        while (entry && (!strcmp (entry->d_name, ".") ||\
                            !strcmp (entry->d_name, ".."))) {\
                                entry = readdir (dir);\
                        }\
                }\
        } while (0); \


typedef enum {
        GD_STORE_SUCCESS,
        GD_STORE_KEY_NULL,
        GD_STORE_VALUE_NULL,
        GD_STORE_KEY_VALUE_NULL,
        GD_STORE_EOF,
        GD_STORE_ENOMEM,
        GD_STORE_STAT_FAILED
} glusterd_store_op_errno_t;

int32_t
glusterd_store_volinfo (glusterd_volinfo_t *volinfo, glusterd_volinfo_ver_ac_t ac);

int32_t
glusterd_store_delete_volume (glusterd_volinfo_t *volinfo);

int32_t
glusterd_store_uuid ();

int32_t
glusterd_store_handle_new (char *path, glusterd_store_handle_t **handle);

int32_t
glusterd_store_save_value (int fd, char *key, char *value);

int32_t
glusterd_store_retrieve_value (glusterd_store_handle_t *handle,
                               char *key, char **value);

int32_t
glusterd_retrieve_uuid ();

int32_t
glusterd_store_peerinfo (glusterd_peerinfo_t *peerinfo);

int32_t
glusterd_store_delete_peerinfo (glusterd_peerinfo_t *peerinfo);

int32_t
glusterd_store_delete_brick (glusterd_volinfo_t *volinfo,
                             glusterd_brickinfo_t *brickinfo);

int32_t
glusterd_store_handle_destroy (glusterd_store_handle_t *handle);

int32_t
glusterd_restore ();

void
glusterd_perform_volinfo_version_action (glusterd_volinfo_t *volinfo,
                                         glusterd_volinfo_ver_ac_t ac);
gf_boolean_t
glusterd_store_is_valid_brickpath (char *volname, char *brick);

int32_t
glusterd_store_perform_node_state_store (glusterd_volinfo_t *volinfo);
#endif
