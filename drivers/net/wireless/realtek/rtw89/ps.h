/* SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause */
/* Copyright(c) 2019-2020  Realtek Corporation
 */

#ifndef __RTW89_PS_H_
#define __RTW89_PS_H_

<<<<<<< HEAD
void rtw89_enter_lps(struct rtw89_dev *rtwdev, struct rtw89_vif *rtwvif);
=======
void rtw89_enter_lps(struct rtw89_dev *rtwdev, u8 mac_id);
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
void rtw89_leave_lps(struct rtw89_dev *rtwdev);
void __rtw89_leave_ps_mode(struct rtw89_dev *rtwdev);
void rtw89_leave_ps_mode(struct rtw89_dev *rtwdev);
void rtw89_enter_ips(struct rtw89_dev *rtwdev);
void rtw89_leave_ips(struct rtw89_dev *rtwdev);
void rtw89_set_coex_ctrl_lps(struct rtw89_dev *rtwdev, bool btc_ctrl);
<<<<<<< HEAD
void rtw89_process_p2p_ps(struct rtw89_dev *rtwdev, struct ieee80211_vif *vif);
=======
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

#endif
