/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _HID_VIVALDI_COMMON_H
#define _HID_VIVALDI_COMMON_H

struct hid_device;
struct hid_field;
<<<<<<< HEAD
=======
struct hid_input;
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
struct hid_usage;

void vivaldi_feature_mapping(struct hid_device *hdev,
			     struct hid_field *field, struct hid_usage *usage);

<<<<<<< HEAD
extern const struct attribute_group *vivaldi_attribute_groups[];
=======
int vivaldi_input_configured(struct hid_device *hdev,
			     struct hid_input *hidinput);
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

#endif /* _HID_VIVALDI_COMMON_H */
