/* SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause) */
/* Copyright (c) 2023, Oracle and/or its affiliates. */

#include <bpftune/bpftune.bpf.h>

/* fire when coredump sysctls are read */
BPF_FENTRY(proc_dostring_coredump, struct ctl_table *table, int write,
				   void *buffer, size_t *lenp, loff_t *ppos)
{
	struct bpftune_event event = {};
	int ret, scenario_id = 0;

	event.tuner_id = tuner_id;
	event.scenario_id = scenario_id;
	ret = bpf_ringbuf_output(&ring_buffer_map, &event, sizeof(event), 0);
	bpftune_debug("tuner [%d] scenario [%d]: event send: %d ",
		      tuner_id, scenario_id, ret);
	return 0;
}
