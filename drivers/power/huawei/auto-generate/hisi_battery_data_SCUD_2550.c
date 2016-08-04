
/* DO NOT EDIT - Generated automatically by build.py */

static struct single_row_lut SCUD_2550_fcc_temp = {
	.x		= {-20, -10, 0, 25, 40, 60},
	.y		= {2576, 2580, 2586, 2634, 2609, 2583},
	.cols	= 6
};

static struct single_row_lut SCUD_2550_fcc_sf = {
	.x		= {0, 100, 200, 300, 400, 500},
	.y		= {100, 96, 94, 92, 90, 88},
	.cols	= 6
};

static struct sf_lut SCUD_2550_pc_sf = {
	.rows = 1,
	.cols = 1,
	.row_entries = {0},
	.percent = {100},
	.sf = {
		{100}
	}
};


static struct sf_lut SCUD_2550_rbatt_sf = {
	.rows = 28,
	.cols = 6,
	.row_entries = {-20, -10, 0, 25, 40, 60},
	.percent = {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
	.sf = {
		{2489, 1561, 755, 159, 118, 107},
		{2487, 1560, 755, 159, 118, 107},
		{2345, 1528, 758, 159, 119, 107},
		{2260, 1497, 765, 163, 121, 108},
		{2186, 1500, 803, 170, 125, 109},
		{1954, 1347, 798, 182, 131, 112},
		{1939, 1258, 729, 189, 135, 115},
		{1932, 1249, 706, 213, 146, 121},
		{1935, 1224, 681, 205, 154, 126},
		{1957, 1228, 649, 170, 139, 120},
		{2017, 1271, 648, 152, 121, 110},
		{2088, 1339, 684, 154, 120, 109},
		{2158, 1417, 746, 157, 124, 112},
		{2248, 1506, 825, 160, 128, 116},
		{2356, 1601, 916, 163, 132, 115},
		{2503, 1694, 1008, 163, 127, 107},
		{2701, 1793, 1101, 162, 120, 108},
		{2951, 1961, 1245, 164, 120, 108},
		{4678, 2226, 1137, 158, 114, 106},
		{5077, 2383, 1214, 160, 120, 112},
		{5397, 2582, 1309, 162, 126, 108},
		{5773, 2806, 1443, 165, 119, 114},
		{6206, 3087, 1604, 169, 125, 114},
		{6589, 3394, 1790, 176, 128, 114},
		{6993, 3571, 1877, 212, 141, 118},
		{6965, 3517, 1892, 187, 123, 116},
		{8033, 4280, 2301, 327, 137, 132},
		{9485, 5264, 2709, 250, 159, 225},
	}
};

static struct pc_temp_ocv_lut SCUD_2550_pc_temp_ocv = {
	.rows = 29,
	.cols = 6,
	.temp = {-20, -10, 0, 25, 40, 60},
	.percent = {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
	.ocv = {
		{4327, 4326, 4325, 4325, 4316, 4309},
		{4226, 4235, 4245, 4261, 4255, 4250},
		{4162, 4172, 4185, 4205, 4199, 4195},
		{4112, 4120, 4131, 4152, 4146, 4142},
		{4063, 4079, 4086, 4101, 4095, 4091},
		{3969, 4001, 4031, 4054, 4048, 4044},
		{3928, 3941, 3969, 3997, 3998, 4000},
		{3892, 3904, 3927, 3961, 3963, 3960},
		{3861, 3867, 3887, 3920, 3922, 3920},
		{3836, 3839, 3849, 3875, 3878, 3877},
		{3818, 3822, 3822, 3842, 3843, 3843},
		{3801, 3809, 3805, 3819, 3819, 3819},
		{3784, 3797, 3794, 3801, 3801, 3799},
		{3768, 3785, 3785, 3785, 3785, 3783},
		{3753, 3772, 3776, 3773, 3771, 3765},
		{3741, 3755, 3762, 3760, 3754, 3740},
		{3730, 3734, 3740, 3742, 3732, 3718},
		{3717, 3717, 3717, 3710, 3703, 3691},
		{3694, 3704, 3696, 3689, 3681, 3669},
		{3687, 3698, 3692, 3688, 3680, 3668},
		{3678, 3693, 3688, 3686, 3679, 3666},
		{3667, 3686, 3683, 3684, 3677, 3665},
		{3656, 3679, 3676, 3680, 3673, 3660},
		{3640, 3667, 3664, 3670, 3662, 3644},
		{3616, 3641, 3639, 3639, 3628, 3606},
		{3555, 3584, 3592, 3586, 3578, 3554},
		{3485, 3515, 3531, 3521, 3510, 3485},
		{3392, 3421, 3437, 3418, 3408, 3387},
		{3200, 3200, 3200, 3200, 3200, 3200},
	}
};

struct hisi_smartstar_coul_battery_data SCUD_2550_battery_data = {
	.id_voltage_min = 1240,
	.id_voltage_max = 1440,
	.fcc = 2550,
	.fcc_temp_lut  = &SCUD_2550_fcc_temp,
	.fcc_sf_lut = &SCUD_2550_fcc_sf,
	.pc_temp_ocv_lut = &SCUD_2550_pc_temp_ocv,
	.pc_sf_lut = &SCUD_2550_pc_sf,
	.rbatt_sf_lut = &SCUD_2550_rbatt_sf,
	.default_rbatt_mohm = 100,
	.max_currentmA = 1000,
    .max_voltagemV = 4352,
    .max_cin_currentmA = 1200,
    .terminal_currentmA = 100,
    .charge_in_temp_5 = 3,
    .charge_in_temp_10 = 3,
    .batt_brand = "CHM-SCUD-2550",
};
