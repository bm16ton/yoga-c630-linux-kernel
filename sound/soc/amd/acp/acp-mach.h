/* SPDX-License-Identifier: (GPL-2.0-only OR BSD-3-Clause) */
/*
 * This file is provided under a dual BSD/GPLv2 license. When using or
 * redistributing this file, you may do so under either license.
 *
 * Copyright(c) 2021 Advanced Micro Devices, Inc. All rights reserved.
 *
 * Author: Ajit Kumar Pandey <AjitKumar.Pandey@amd.com>
 */
#ifndef __ACP_MACH_H
#define __ACP_MACH_H

#include <sound/core.h>
#include <sound/jack.h>
#include <sound/pcm_params.h>
#include <sound/soc-dapm.h>
#include <linux/input.h>
#include <linux/module.h>
#include <sound/soc.h>
<<<<<<< HEAD
=======
#include <linux/gpio.h>
#include <linux/gpio/consumer.h>

#define EN_SPKR_GPIO_GB                0x11F
#define EN_SPKR_GPIO_NONE      -EINVAL
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

enum be_id {
	HEADSET_BE_ID = 0,
	AMP_BE_ID,
	DMIC_BE_ID,
};

enum cpu_endpoints {
	NONE = 0,
<<<<<<< HEAD
	I2S_HS,
=======
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
	I2S_SP,
	I2S_BT,
	DMIC,
};

enum codec_endpoints {
	DUMMY = 0,
	RT5682,
	RT1019,
	MAX98360A,
	RT5682S,
<<<<<<< HEAD
	NAU8825,
};

enum platform_end_point {
	RENOIR = 0,
	REMBRANDT,
=======
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
};

struct acp_card_drvdata {
	unsigned int hs_cpu_id;
	unsigned int amp_cpu_id;
	unsigned int dmic_cpu_id;
	unsigned int hs_codec_id;
	unsigned int amp_codec_id;
	unsigned int dmic_codec_id;
	unsigned int dai_fmt;
<<<<<<< HEAD
	unsigned int platform;
	struct clk *wclk;
	struct clk *bclk;
	bool soc_mclk;
=======
	struct clk *wclk;
	struct clk *bclk;
	unsigned int gpio_spkr_en;
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
};

int acp_sofdsp_dai_links_create(struct snd_soc_card *card);
int acp_legacy_dai_links_create(struct snd_soc_card *card);
<<<<<<< HEAD

=======
int event_spkr_handler(struct snd_soc_dapm_widget *w,
			struct snd_kcontrol *k, int event);
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
#endif
