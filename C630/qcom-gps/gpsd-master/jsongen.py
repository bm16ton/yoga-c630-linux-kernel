#!/usr/bin/env python
#
# This file is Copyright (c) 2010 by the GPSD project
# SPDX-License-Identifier: BSD-2-clause
#
# Never hand-hack what you can generate...
#
# This code generates template declarations for AIS-JSON parsing from a
# declarative specification of a JSON structure.
#
# This code runs compatibly under Python 2 and 3.x for x >= 2.
# Preserve this property!
from __future__ import absolute_import, print_function, division

import getopt
import sys

#
# Here is the information that makes it all work - attribute, type, and
# defult information for all fields.  We generate a JSON
# parser template spec. Doing it this way guarantees consistency.
#
# Notes on the fields:
# initname: becomes the name of the generated structure initializer
# header: common header to include in front of the structure template
# structname: gets prepended to all fieldnames in the generated C
# fieldmap: each member fills an initializer slot
# stringbuffered: list strings that should be buffered rather than copied
#                 directly into the structure.

ais_specs = (
    {
        "initname": "json_ais1",
        "headers": ("AIS_HEADER",),
        "structname": "ais->type1",
        "fieldmap": (
            # fieldname   type        default
            ('status',     'uinteger', '0'),
            ('status_text', 'ignore',   None),
            ('turn',       'integer',  'AIS_TURN_NOT_AVAILABLE'),
            ('speed',      'uinteger', 'AIS_SPEED_NOT_AVAILABLE'),
            ('accuracy',   'boolean',  'false'),
            ('lon',        'integer',  'AIS_LON_NOT_AVAILABLE'),
            ('lat',        'integer',  'AIS_LAT_NOT_AVAILABLE'),
            ('course',     'uinteger', 'AIS_COURSE_NOT_AVAILABLE'),
            ('heading',    'uinteger', 'AIS_HEADING_NOT_AVAILABLE'),
            ('second',     'uinteger', 'AIS_SEC_NOT_AVAILABLE'),
            ('maneuver',   'uinteger', 'AIS_SEC_INOPERATIVE'),
            ('raim',       'boolean',  'false'),
            ('radio',      'uinteger', '0'),
        ),
    },
    # Message types 2 and 3 duplicate 1
    {
        "initname": "json_ais4",
        "headers": ("AIS_HEADER",),
        "structname": "ais->type4",
        "fieldmap": (
            # fieldname   type        default
            ('timestamp', 'string',   None),
            ('accuracy',  'boolean',  "true"),
            ('lon',       'integer',  "AIS_LON_NOT_AVAILABLE"),
            ('lat',       'integer',  "AIS_LAT_NOT_AVAILABLE"),
            ('epfd',      'uinteger', "0"),
            ('epfd_text', 'ignore',   None),
            ('raim',      'boolean',  "false"),
            ('radio',     'uinteger', "0"),
        ),
        "stringbuffered": ("timestamp",),
    },
    {
        "initname": "json_ais5",
        "headers": ("AIS_HEADER",),
        "structname": "ais->type5",
        "fieldmap": (
            # fieldname        type            default
            ('imo',           'uinteger',      '0'),
            ('ais_version',   'uinteger',      '0'),
            ('callsign',      'string',        None),
            ('shipname',      'string',        None),
            ('shiptype',      'uinteger',      '0'),
            ('shiptype_text', 'ignore',        None),
            ('to_bow',        'uinteger',      '0'),
            ('to_stern',      'uinteger',      '0'),
            ('to_port',       'uinteger',      '0'),
            ('to_starboard',  'uinteger',      '0'),
            ('epfd',          'uinteger',      '0'),
            ('epfd_text',     'ignore',        None),
            ('eta',           'string',        None),
            ('draught',       'uinteger',      '0'),
            ('destination',   'string',        None),
            ('dte',           'uinteger',      '1'),
        ),
        "stringbuffered": ("eta",),
    },
    {
        "initname": "json_ais6",
        "headers": ("AIS_HEADER", "AIS_TYPE6",),
        "structname": "ais->type6",
        "fieldmap": (
            # fieldname       type             default
            ('data',          'string',        None),
        ),
        "stringbuffered": ("data",),
    },
    {
        "initname": "json_ais6_fid10",
        "headers": ("AIS_HEADER", "AIS_TYPE6",),
        "structname": "ais->type6.dac235fid10",
        "fieldmap": (
            # fieldname    type        default
            ('ana_int',    'uinteger', '0'),
            ('ana_ext1',   'uinteger', '0'),
            ('ana_ext2',   'uinteger', '0'),
            ('racon',      'uinteger', '0'),
            ('racon_text', 'ignore',   None),
            ('light',      'uinteger', '0'),
            ('light_text', 'ignore',   None),
            ('alarm',      'boolean',  'false'),
            ('stat_ext',   'uinteger', '0'),
            ('off_pos',    'boolean',  'false'),
        ),
    },
    {
        "initname": "json_ais6_fid12",
        "headers": ("AIS_HEADER", "AIS_TYPE6",),
        "structname": "ais->type6.dac1fid12",
        "fieldmap": (
            # fieldname    type      default
            ('lastport',   'string',   None),
            ('departure',  'string',   None),
            ('nextport',   'string',   None),
            ('eta',        'string',   None),
            ('dangerous',  'string',   None),
            ('imdcat',     'string',   None),
            ('unid',       'uinteger', '0'),
            ('amount',     'uinteger', '0'),
            ('unit',       'uinteger', '0'),
        ),
        "stringbuffered": ("departure", "eta",),
    },
    {
        "initname": "json_ais6_fid15",
        "headers": ("AIS_HEADER", "AIS_TYPE6",),
        "structname": "ais->type6.dac1fid15",
        "fieldmap": (
            # fieldname    type        default
            ('airdraught', 'uinteger', '0'),
        ),
    },
    {
        "initname": "json_ais6_fid16",
        "headers": ("AIS_HEADER", "AIS_TYPE6",),
        "structname": "ais->type6.dac1fid16",
        "fieldmap": (
            # fieldname           type             default
            ('persons',           'uinteger',      '0'),
        ),
    },
    {
        "initname": "json_ais6_fid18",
        "headers": ("AIS_HEADER", "AIS_TYPE6",),
        "structname": "ais->type6.dac1fid18",
        "fieldmap": (
            # fieldname    type        default
            ('linkage',    'uinteger', '0'),
            ('arrival',    'string',   None),
            ('portname',   'string',   None),
            ('destination', 'string',   None),
            ('lon',        'integer',  'AIS_LON3_NOT_AVAILABLE'),
            ('lat',        'integer',  'AIS_LAT3_NOT_AVAILABLE'),
        ),
        'stringbuffered': ('arrival',),
    },
    {
        "initname": "json_ais6_fid20",
        "headers": ("AIS_HEADER", "AIS_TYPE6",),
        "structname": "ais->type6.dac1fid20",
        "fieldmap": (
            # fieldname    type        default
            ('linkage',    'uinteger', '0'),
            ('berth_length', 'uinteger', '0'),
            ('berth_depth', 'uinteger', '0'),
            ('position',   'uinteger', '0'),
            ('position_text', 'ignore', None),
            ('arrival',    'string', None),
            ('availability', 'uinteger', '0'),
            ('agent',      'uinteger', '0'),
            ('fuel',       'uinteger', '0'),
            ('chandler',   'uinteger', '0'),
            ('stevedore',  'uinteger', '0'),
            ('electrical', 'uinteger', '0'),
            ('water',      'uinteger', '0'),
            ('customs',    'uinteger', '0'),
            ('cartage',    'uinteger', '0'),
            ('crane',      'uinteger', '0'),
            ('lift',       'uinteger', '0'),
            ('medical',    'uinteger', '0'),
            ('navrepair',  'uinteger', '0'),
            ('provisions', 'uinteger', '0'),
            ('shiprepair', 'uinteger', '0'),
            ('surveyor',   'uinteger', '0'),
            ('steam',      'uinteger', '0'),
            ('tugs',       'uinteger', '0'),
            ('solidwaste',  'uinteger', '0'),
            ('liquidwaste', 'uinteger', '0'),
            ('hazardouswaste', 'uinteger', '0'),
            ('ballast',    'uinteger', '0'),
            ('additional', 'uinteger', '0'),
            ('regional1',  'uinteger', '0'),
            ('regional2',  'uinteger', '0'),
            ('future1',    'uinteger', '0'),
            ('future2',    'uinteger', '0'),
            ('berth_name', 'string',   None),
            ('berth_lon',  'integer',  'AIS_LON3_NOT_AVAILABLE'),
            ('berth_lat',  'integer',  'AIS_LAT3_NOT_AVAILABLE'),
        ),
        'stringbuffered': ('arrival', 'berth_name',),
    },
    {
        "initname": "json_ais6_fid21",
        "headers": ("AIS_HEADER", "AIS_TYPE6"),
        "structname": "ais->type6.dac200fid21",
        "fieldmap": (
            # fieldname    type        default
            ('country',    'string',   None),
            ('locode',     'string',   None),
            ('section',    'string',   None),
            ('terminal',   'string',   None),
            ('hectometre', 'string',   None),
            ('eta',        'string',   None),
            ('tugs',       'uinteger', '0'),
            ('airdraught', 'uinteger', '0'),
        ),
        "stringbuffered": ("eta",),
    },
    {
        "initname": "json_ais6_fid22",
        "headers": ("AIS_HEADER", "AIS_TYPE6"),
        "structname": "ais->type6.dac200fid22",
        "fieldmap": (
            # fieldname    type        default
            ('country',    'string',   None),
            ('locode',     'string',   None),
            ('section',    'string',   None),
            ('terminal',   'string',   None),
            ('hectometre', 'string',   None),
            ('rta',        'string',   None),
            ('status',     'uinteger', 'DAC200FID22_STATUS_NOT_AVAILABLE'),
        ),
        "stringbuffered": ("rta",),
    },
    {
        "initname": "json_ais6_fid25",
        "headers": ("AIS_HEADER", "AIS_TYPE6",),
        "structname": "ais->type6.dac1fid25",
        "fieldmap": (
            # fieldname    type        default
            ('unit',       'uinteger', '0'),
            ('amount',     'uinteger', '0'),
            ('cargos',     'array',    (
                ('cargo_t', 'ncargos', (
                    ('code',       'uinteger', '0'),
                    ('subtype',    'uinteger', '0'),
                )))),
        ),
    },
    {
        "initname": "json_ais6_fid28",
        "headers": ("AIS_HEADER", "AIS_TYPE6",),
        "structname": "ais->type6.dac1fid28",
        "fieldmap": (
            # fieldname    type        default
            ('linkage',    'uinteger', '0'),
            ('sender',     'uinteger', '0'),
            ('rtype',      'uinteger', '0'),
            ('rtype_text', 'ignore',   None),
            ('start',      'string',   None),
            ('duration',   'uinteger', '0'),
            ('waypoints',  'array', (
                ('waypoint_t', 'waycount', (
                    ('lon',        'integer',  'AIS_LON4_NOT_AVAILABLE'),
                    ('lat',        'integer',  'AIS_LAT4_NOT_AVAILABLE'),
                )))),
        ),
        'stringbuffered': ('start',),
    },
    {
        "initname": "json_ais6_fid30",
        "headers": ("AIS_HEADER", "AIS_TYPE6",),
        "structname": "ais->type6.dac1fid30",
        "fieldmap": (
            # fieldname     type             default
            ('linkage',     'uinteger',      '0'),
            ('text',        'string',        '0'),
        ),
    },
    {
        "initname": "json_ais6_fid32",
        "headers": ("AIS_HEADER", "AIS_TYPE6"),
        "structname": "ais->type6.dac1fid32",
        "fieldmap": (
            # fieldname    type        default
            ('month',      'uinteger', 'AIS_MONTH_NOT_AVAILABLE'),
            ('day',        'uinteger', 'AIS_DAY_NOT_AVAILABLE'),
            ('tidals',     'array', (
                ('tidal_t', 'ntidals', (
                    ('lon', 'integer',  'AIS_LON3_NOT_AVAILABLE'),
                    ('lat', 'integer',  'AIS_LAT3_NOT_AVAILABLE'),
                    ('from_hour', 'uinteger', 'AIS_MONTH_NOT_AVAILABLE'),
                    ('from_min', 'uinteger', 'AIS_MINUTE_NOT_AVAILABLE'),
                    ('to_hour', 'uinteger', 'AIS_HOUR_NOT_AVAILABLE'),
                    ('to_min', 'uinteger', 'AIS_MINUTE_NOT_AVAILABLE'),
                    ('cdir', 'uinteger', 'DAC1FID32_CDIR_NOT_AVAILABLE'),
                    ('cspeed', 'uinteger', 'DAC1FID32_CSPEED_NOT_AVAILABLE'),
                )))),
        ),
    },
    {
        "initname": "json_ais6_fid55",
        "headers": ("AIS_HEADER", "AIS_TYPE6"),
        "structname": "ais->type6.dac200fid55",
        "fieldmap": (
            # fieldname    type        default
            ('crew',       'uinteger', 'DAC200FID55_COUNT_NOT_AVAILABLE'),
            ('passengers', 'uinteger', 'DAC200FID55_COUNT_NOT_AVAILABLE'),
            ('personnel',  'uinteger', 'DAC200FID55_COUNT_NOT_AVAILABLE'),
        ),
    },
    {
        "initname": "json_ais7",
        "headers": ("AIS_HEADER",),
        "structname": "ais->type7",
        "fieldmap": (
            # fieldname       type             default
            ('mmsi1',         'uinteger',      '0'),
            ('mmsi2',         'uinteger',      '0'),
            ('mmsi3',         'uinteger',      '0'),
            ('mmsi4',         'uinteger',      '0'),
            ('seqno1',        'uinteger',      '0'),
            ('seqno2',        'uinteger',      '0'),
            ('seqno3',        'uinteger',      '0'),
            ('seqno4',        'uinteger',      '0'),
        ),
    },
    {
        "initname": "json_ais8",
        "headers": ("AIS_HEADER", "AIS_TYPE8",),
        "structname": "ais->type8",
        "fieldmap": (
            # fieldname       type             default
            ('data',          'string',        None),
        ),
        "stringbuffered": ("data",),
    },
    {
        "initname": "json_ais8_fid10",
        "headers": ("AIS_HEADER", "AIS_TYPE8",),
        "structname": "ais->type8.dac200fid10",
        "fieldmap": (
            # fieldname    type        default
            ('vin',        'string',   None),
            ('length',     'uinteger', '0'),
            ('beam',       'uinteger', '0'),
            ('shiptype',   'uinteger', '0'),
            ('shiptype_text',  'ignore',   None),
            ('hazard',     'uinteger', '0'),
            ('hazard_text', 'ignore',   None),
            ('draught',    'uinteger', '0'),
            ('loaded',     'uinteger', '0'),
            ('loaded_text', 'ignore',   None),
            ('speed_q',    'boolean',  'false'),
            ('course_q',   'boolean',  'false'),
            ('heading_q',  'boolean',  'false'),
        ),
    },
    {
        "initname": "json_ais8_fid11",
        "headers": ("AIS_HEADER", "AIS_TYPE8",),
        "structname": "ais->type8.dac1fid11",
        "fieldmap": (
            # fieldname      type         default
            ('lat',          'integer',   'DAC1FID11_LAT_NOT_AVAILABLE'),
            ('lon',          'integer',   'DAC1FID11_LON_NOT_AVAILABLE'),
            ('timestamp',    'string',     None),
            ('wspeed',       'uinteger',  'DAC1FID11_WSPEED_NOT_AVAILABLE'),
            ('wgust',        'uinteger',  'DAC1FID11_WSPEED_NOT_AVAILABLE'),
            ('wdir',         'uinteger',  'DAC1FID11_WDIR_NOT_AVAILABLE'),
            ('wgustdir',     'uinteger',  'DAC1FID11_WDIR_NOT_AVAILABLE'),
            ('airtemp',      'uinteger',  'DAC1FID11_AIRTEMP_NOT_AVAILABLE'),
            ('humidity',     'uinteger',  'DAC1FID11_HUMIDITY_NOT_AVAILABLE'),
            ('dewpoint',     'uinteger',  'DAC1FID11_DEWPOINT_NOT_AVAILABLE'),
            ('pressure',     'uinteger',  'DAC1FID11_PRESSURE_NOT_AVAILABLE'),
            ('pressuretend', 'uinteger',
             'DAC1FID11_PRESSURETREND_NOT_AVAILABLE'),
            ('visibility', 'uinteger',  'DAC1FID11_VISIBILITY_NOT_AVAILABLE'),
            ('waterlevel', 'integer',   'DAC1FID11_WATERLEVEL_NOT_AVAILABLE'),
            ('leveltrend', 'uinteger',
             'DAC1FID11_WATERLEVELTREND_NOT_AVAILABLE'),
            ('cspeed',       'uinteger',  'DAC1FID11_CSPEED_NOT_AVAILABLE'),
            ('cdir',         'uinteger',  'DAC1FID11_CDIR_NOT_AVAILABLE'),
            ('cspeed2',      'uinteger',  'DAC1FID11_CSPEED_NOT_AVAILABLE'),
            ('cdir2',        'uinteger',  'DAC1FID11_CDIR_NOT_AVAILABLE'),
            ('cdepth2',      'uinteger',  'DAC1FID11_CDEPTH_NOT_AVAILABLE'),
            ('cspeed3',      'uinteger',  'DAC1FID11_CSPEED_NOT_AVAILABLE'),
            ('cdir3',        'uinteger',  'DAC1FID11_CDIR_NOT_AVAILABLE'),
            ('cdepth3',      'uinteger',  'DAC1FID11_CDEPTH_NOT_AVAILABLE'),
            ('waveheight', 'uinteger',  'DAC1FID11_WAVEHEIGHT_NOT_AVAILABLE'),
            ('waveperiod', 'uinteger',  'DAC1FID11_WAVEPERIOD_NOT_AVAILABLE'),
            ('wavedir',    'uinteger',  'DAC1FID11_WAVEDIR_NOT_AVAILABLE'),
            ('swellheight', 'uinteger',  'DAC1FID11_WAVEHEIGHT_NOT_AVAILABLE'),
            ('swellperiod', 'uinteger',  'DAC1FID11_WAVEPERIOD_NOT_AVAILABLE'),
            ('swelldir',    'uinteger',  'DAC1FID11_WAVEDIR_NOT_AVAILABLE'),
            ('seastate',    'uinteger',  'DAC1FID11_SEASTATE_NOT_AVAILABLE'),
            ('watertemp',   'uinteger',  'DAC1FID11_WATERTEMP_NOT_AVAILABLE'),
            ('preciptype',  'uinteger',  'DAC1FID11_PRECIPTYPE_NOT_AVAILABLE'),
            ('preciptype_text', 'ignore', None),
            ('salinity',    'uinteger',  'DAC1FID11_SALINITY_NOT_AVAILABLE'),
            ('ice',         'uinteger',  'DAC1FID11_ICE_NOT_AVAILABLE'),
            ('ice_text',    'ignore',    None),
        ),
        "stringbuffered": ("timestamp",),
    },
    {
        "initname": "json_ais8_fid13",
        "headers": ("AIS_HEADER", "AIS_TYPE8",),
        "structname": "ais->type8.dac1fid13",
        "fieldmap": (
            # fieldname    type        default
            ('reason',     'string',   None),
            ('closefrom',  'string',   None),
            ('closeto',    'string',   None),
            ('radius',     'uinteger', 'AIS_DAC1FID13_RADIUS_NOT_AVAILABLE'),
            ('extunit',    'uinteger', 'AIS_DAC1FID13_EXTUNIT_NOT_AVAILABLE'),
            ('fday',       'uinteger', 'AIS_DAY_NOT_AVAILABLE'),
            ('fmonth',     'uinteger', 'AIS_MONTH_NOT_AVAILABLE'),
            ('fhour',      'uinteger', 'AIS_HOUR_NOT_AVAILABLE'),
            ('fminute',    'uinteger', 'AIS_MINUTE_NOT_AVAILABLE'),
            ('tday',       'uinteger', 'AIS_DAY_NOT_AVAILABLE'),
            ('tmonth',     'uinteger', 'AIS_MONTH_NOT_AVAILABLE'),
            ('thour',      'uinteger', 'AIS_HOUR_NOT_AVAILABLE'),
            ('tminute',    'uinteger', 'AIS_MINUTE_NOT_AVAILABLE'),
        ),
        'stringbuffered': ('closefrom', 'closeto'),
    },
    {
        "initname": "json_ais8_fid15",
        "headers": ("AIS_HEADER", "AIS_TYPE8",),
        "structname": "ais->type8.dac1fid15",
        "fieldmap": (
            # fieldname    type        default
            ('airdraught', 'uinteger', '0'),
        ),
    },
    {
        "initname": "json_ais8_fid16",
        "headers": ("AIS_HEADER", "AIS_TYPE8",),
        "structname": "ais->type8.dac1fid16",
        "fieldmap": (
            # fieldname           type             default
            ('persons',           'uinteger',      '0'),
        ),
    },
    {
        "initname": "json_ais8_fid17",
        "headers": ("AIS_HEADER", "AIS_TYPE8",),
        "structname": "ais->type8.dac1fid17",
        "fieldmap": (
            # fieldname    type        default
            ('targets',    'array', (
                ('target_t', 'ntargets', (
                    ('idtype',     'uinteger', 'DAC1FID17_IDTYPE_OTHER'),
                    ("id.mmsi",    'uinteger', '0'),
                    ("id.imo",     'uinteger', '0'),
                    ("id.callsign", 'string',   'DAC1FID17_ID_LENGTH'),
                    ("id.other",   'string',   'DAC1FID17_ID_LENGTH'),
                    ('lat',        'integer',  'AIS_LAT3_NOT_AVAILABLE'),
                    ('lon',        'integer',  'AIS_LON3_NOT_AVAILABLE'),
                    ('course', 'uinteger', 'DAC1FID17_COURSE_NOT_AVAILABLE'),
                    ('second', 'uinteger', 'AIS_SECOND_NOT_AVAILABLE'),
                    ('speed', 'uinteger', 'DAC1FID17_SPEED_NOT_AVAILABLE'),
                )))),
        ),
    },
    {
        "initname": "json_ais8_fid19",
        "headers": ("AIS_HEADER", "AIS_TYPE8",),
        "structname": "ais->type8.dac1fid19",
        "fieldmap": (
            # fieldname    type        default
            ('linkage',    'uinteger', '0'),
            ('station',    'string',   None),
            ('lon',        'integer',  'AIS_LON3_NOT_AVAILABLE'),
            ('lat',        'integer',  'AIS_LAT3_NOT_AVAILABLE'),
            ('status',     'uinteger', '0'),
            ('signal',     'uinteger', '0'),
            ('signal_text', 'ignore',    None),
            ('hour',       'uinteger', 'AIS_HOUR_NOT_AVAILABLE'),
            ('minute',     'uinteger', 'AIS_MINUTE_NOT_AVAILABLE'),
            ('nextsignal', 'uinteger', '0'),
            ('nextsignal_type', 'ignore', None),
        ),
    },
    {
        "initname": "json_ais8_fid23",
        "headers": ("AIS_HEADER", "AIS_TYPE8"),
        "structname": "ais->type8.dac200fid23",
        "fieldmap": (
            # fieldname    type        default
            ('start',      'string',   None),
            ('end',        'string',   None),
            ('start_lon',  'integer',  'AIS_LON4_NOT_AVAILABLE'),
            ('start_lat',  'integer',  'AIS_LAT4_NOT_AVAILABLE'),
            ('end_lon',    'integer',  'AIS_LON4_NOT_AVAILABLE'),
            ('end_lat',    'integer',  'AIS_LAT4_NOT_AVAILABLE'),
            ('type',       'uinteger', 'DAC200FID23_TYPE_UNKNOWN'),
            ('type_text',  'ignore',   None),
            ('min',        'integer',  'DAC200FID23_MIN_UNKNOWN'),
            ('max',        'integer',  'DAC200FID23_MAX_UNKNOWN'),
            ('intensity',  'uinteger', 'DAC200FID23_CLASS_UNKNOWN'),
            ('intensity_text', 'ignore',   None),
            ('wind',       'uinteger', 'DAC200FID23_WIND_UNKNOWN'),
            ('wind_text',  'ignore',   None),
        ),
        'stringbuffered': ('start', 'end'),
    },
    {
        "initname": "json_ais8_fid24",
        "headers": ("AIS_HEADER", "AIS_TYPE8"),
        "structname": "ais->type8.dac200fid24",
        "fieldmap": (
            # fieldname    type        default
            ('country',    'string',   None),
            ('gauges',     'array', (
                ('gauge_t', 'ngauges', (
                    ('id', 'uinteger', 'DAC200FID24_GAUGE_ID_UNKNOWN'),
                    ('level', 'integer', 'DAC200FID24_GAUGE_LEVEL_UNKNOWN'),
                )))),
        ),
    },
    {
        "initname": "json_ais8_fid27",
        "headers": ("AIS_HEADER", "AIS_TYPE8",),
        "structname": "ais->type8.dac1fid27",
        "fieldmap": (
            # fieldname    type        default
            ('linkage',    'uinteger', '0'),
            ('sender',     'uinteger', '0'),
            ('rtype',      'uinteger', '0'),
            ('rtype_text', 'ignore',   None),
            ('start',      'string',   None),
            ('duration',   'uinteger', '0'),
            ('waypoints',  'array', (
                ('waypoint_t', 'waycount', (
                    ('lon',        'integer',  'AIS_LON4_NOT_AVAILABLE'),
                    ('lat',        'integer',  'AIS_LAT4_NOT_AVAILABLE'),
                )))),
        ),
        'stringbuffered': ('start',),
    },
    {
        "initname": "json_ais8_fid29",
        "headers": ("AIS_HEADER", "AIS_TYPE8",),
        "structname": "ais->type8.dac1fid29",
        "fieldmap": (
            # fieldname     type             default
            ('linkage',     'uinteger',      '0'),
            ('text',        'string',        '0'),
        ),
    },
    {
        "initname": "json_ais8_fid31",
        "headers": ("AIS_HEADER", "AIS_TYPE8",),
        "structname": "ais->type8.dac1fid31",
        "fieldmap": (
            # fieldname      type         default
            ('lon',        'integer',  'DAC1FID31_LON_NOT_AVAILABLE'),
            ('lat',        'integer',  'DAC1FID31_LAT_NOT_AVAILABLE'),
            ('accuracy',   'boolean',  'false'),
            ('timestamp',    'string',     None),
            ('wspeed',     'uinteger', 'DAC1FID31_WIND_NOT_AVAILABLE'),
            ('wgust',      'uinteger', 'DAC1FID31_WIND_NOT_AVAILABLE'),
            ('wdir',       'uinteger', 'DAC1FID31_DIR_NOT_AVAILABLE'),
            ('wgustdir',   'uinteger', 'DAC1FID31_DIR_NOT_AVAILABLE'),
            ('airtemp',    'integer',  'DAC1FID31_AIRTEMP_NOT_AVAILABLE'),
            ('humidity',   'uinteger', 'DAC1FID31_HUMIDITY_NOT_AVAILABLE'),
            ('dewpoint',   'integer',  'DAC1FID31_DEWPOINT_NOT_AVAILABLE'),
            ('pressure',   'uinteger', 'DAC1FID31_PRESSURE_NOT_AVAILABLE'),
            ('pressuretend', 'uinteger',
             'DAC1FID31_PRESSURETEND_NOT_AVAILABLE'),
            ('visgreater', 'boolean',  'false'),
            ('visibility', 'uinteger', 'DAC1FID31_VISIBILITY_NOT_AVAILABLE'),
            ('waterlevel', 'integer',  'DAC1FID31_WATERLEVEL_NOT_AVAILABLE'),
            ('leveltrend', 'uinteger',
             'DAC1FID31_WATERLEVELTREND_NOT_AVAILABLE'),
            ('cspeed',     'uinteger', 'DAC1FID31_CSPEED_NOT_AVAILABLE'),
            ('cdir',       'uinteger', 'DAC1FID31_DIR_NOT_AVAILABLE'),
            ('cspeed2',    'uinteger', 'DAC1FID31_CSPEED_NOT_AVAILABLE'),
            ('cdir2',      'uinteger', 'DAC1FID31_DIR_NOT_AVAILABLE'),
            ('cdepth2',    'uinteger', 'DAC1FID31_CDEPTH_NOT_AVAILABLE'),
            ('cspeed3',    'uinteger', 'DAC1FID31_CSPEED_NOT_AVAILABLE'),
            ('cdir3',      'uinteger', 'DAC1FID31_DIR_NOT_AVAILABLE'),
            ('cdepth3',    'uinteger', 'DAC1FID31_CDEPTH_NOT_AVAILABLE'),
            ('waveheight', 'uinteger', 'DAC1FID31_HEIGHT_NOT_AVAILABLE'),
            ('waveperiod', 'uinteger', 'DAC1FID31_PERIOD_NOT_AVAILABLE'),
            ('wavedir',    'uinteger', 'DAC1FID31_DIR_NOT_AVAILABLE'),
            ('swellheight', 'uinteger', 'DAC1FID31_HEIGHT_NOT_AVAILABLE'),
            ('swellperiod', 'uinteger', 'DAC1FID31_PERIOD_NOT_AVAILABLE'),
            ('swelldir',   'uinteger', 'DAC1FID31_DIR_NOT_AVAILABLE'),
            ('seastate',   'uinteger', 'DAC1FID31_SEASTATE_NOT_AVAILABLE'),
            ('watertemp',  'integer',  'DAC1FID31_WATERTEMP_NOT_AVAILABLE'),
            ('preciptype', 'uinteger', 'DAC1FID31_PRECIPTYPE_NOT_AVAILABLE'),
            ('preciptype_text', 'ignore', None),
            ('salinity',   'uinteger', 'DAC1FID31_SALINITY_NOT_AVAILABLE'),
            ('ice',        'uinteger', 'DAC1FID31_ICE_NOT_AVAILABLE'),
        ),
        "stringbuffered": ("timestamp",),
    },
    {
        "initname": "json_ais8_fid40",
        "headers": ("AIS_HEADER", "AIS_TYPE8"),
        "structname": "ais->type8.dac200fid40",
        "fieldmap": (
            # fieldname    type        default
            ('form',       'uinteger', 'DAC200FID40_FORM_UNKNOWN'),
            ('facing',     'uinteger', 'DAC200FID40_FACING_UNKNOWN'),
            ('direction',  'uinteger', 'DAC200FID40_DIRECTION_UNKNOWN'),
            ('direction_text', 'ignore',   None),
            ('status',     'uinteger', 'DAC200FID40_STATUS_UNKNOWN'),
            ('status_text', 'ignore',   None),
        ),
    },
    {
        "initname": "json_ais9",
        "headers": ("AIS_HEADER",),
        "structname": "ais->type9",
        "fieldmap": (
            # fieldname       type             default
            ('alt',           'uinteger',      'AIS_ALT_NOT_AVAILABLE'),
            ('speed',         'uinteger',      'AIS_SPEED_NOT_AVAILABLE'),
            ('accuracy',      'boolean',       'false'),
            ('lon',           'integer',       'AIS_LON_NOT_AVAILABLE'),
            ('lat',           'integer',       'AIS_LAT_NOT_AVAILABLE'),
            ('course',        'uinteger',      'AIS_COURSE_NOT_AVAILABLE'),
            ('second',        'uinteger',      'AIS_SEC_NOT_AVAILABLE'),
            ('regional',      'uinteger',      '0'),
            ('dte',           'uinteger',      '1'),
            ('raim',          'boolean',       'false'),
            ('radio',         'uinteger',      '0'),
        ),
    },
    {
        "initname": "json_ais10",
        "headers": ("AIS_HEADER",),
        "structname": "ais->type10",
        "fieldmap": (
            # fieldname       type             default
            ('dest_mmsi',     'uinteger',      '0'),
        ),
    },
    # Message type 11 duplicates 4
    {
        "initname": "json_ais12",
        "headers": ("AIS_HEADER",),
        "structname": "ais->type12",
        "fieldmap": (
            # fieldname       type             default
            ('seqno',         'uinteger',      '0'),
            ('dest_mmsi',     'uinteger',      '0'),
            ('retransmit',    'boolean',       '0'),
            ('text',          'string',        None),
        ),
    },
    # Message type 13 duplicates 7
    {
        "initname": "json_ais14",
        "headers": ("AIS_HEADER",),
        "structname": "ais->type14",
        "fieldmap": (
            # fieldname       type             default
            ('text',          'string',        None),
        ),
    },
    {
        "initname": "json_ais15",
        "headers": ("AIS_HEADER",),
        "structname": "ais->type15",
        "fieldmap": (
            # fieldname       type             default
            ('mmsi1',         'uinteger',      '0'),
            ('type1_1',       'uinteger',      '0'),
            ('offset1_1',     'uinteger',      '0'),
            ('type1_2',       'uinteger',      '0'),
            ('offset1_2',     'uinteger',      '0'),
            ('mmsi2',         'uinteger',      '0'),
            ('type2_1',       'uinteger',      '0'),
            ('offset2_1',     'uinteger',      '0'),
        ),
    },
    {
        "initname": "json_ais16",
        "headers": ("AIS_HEADER",),
        "structname": "ais->type16",
        "fieldmap": (
            # fieldname       type             default
            ('mmsi1',         'uinteger',      '0'),
            ('offset1',       'uinteger',      '0'),
            ('increment1',    'uinteger',      '0'),
            ('mmsi2',         'uinteger',      '0'),
            ('offset2',       'uinteger',      '0'),
            ('increment2',    'uinteger',      '0'),
        ),
    },
    {
        "initname": "json_ais17",
        "headers": ("AIS_HEADER",),
        "structname": "ais->type17",
        "fieldmap": (
            # fieldname       type             default
            ('lon',           'integer',       'AIS_GNS_LON_NOT_AVAILABLE'),
            ('lat',           'integer',       'AIS_GNS_LAT_NOT_AVAILABLE'),
            ('data',          'string',        None),
        ),
        "stringbuffered": ("data",),
    },
    {
        "initname": "json_ais18",
        "headers": ("AIS_HEADER",),
        "structname": "ais->type18",
        "fieldmap": (
            # fieldname       type             default
            ('reserved',      'uinteger',      '0'),
            ('speed',         'uinteger',      'AIS_SPEED_NOT_AVAILABLE'),
            ('accuracy',      'boolean',       'false'),
            ('lon',           'integer',       'AIS_LON_NOT_AVAILABLE'),
            ('lat',           'integer',       'AIS_LAT_NOT_AVAILABLE'),
            ('course',        'uinteger',      'AIS_COURSE_NOT_AVAILABLE'),
            ('heading',       'uinteger',      'AIS_HEADING_NOT_AVAILABLE'),
            ('second',        'uinteger',      'AIS_SEC_NOT_AVAILABLE'),
            ('regional',      'uinteger',      '0'),
            ('cs',            'boolean',       'false'),
            ('display',       'boolean',       'false'),
            ('dsc',           'boolean',       'false'),
            ('band',          'boolean',       'false'),
            ('msg22',         'boolean',       'false'),
            ('raim',          'boolean',       'false'),
            ('radio',         'uinteger',      '0'),
        ),
    },
    {
        "initname": "json_ais19",
        "headers": ("AIS_HEADER",),
        "structname": "ais->type19",
        "fieldmap": (
            # fieldname       type             default
            ('reserved',      'uinteger',      '0'),
            ('speed',         'uinteger',      'AIS_SPEED_NOT_AVAILABLE'),
            ('accuracy',      'boolean',       'false'),
            ('lon',           'integer',       'AIS_LON_NOT_AVAILABLE'),
            ('lat',           'integer',       'AIS_LAT_NOT_AVAILABLE'),
            ('course',        'uinteger',      'AIS_COURSE_NOT_AVAILABLE'),
            ('heading',       'uinteger',      'AIS_HEADING_NOT_AVAILABLE'),
            ('second',        'uinteger',      'AIS_SEC_NOT_AVAILABLE'),
            ('regional',      'uinteger',      '0'),
            ('shipname',      'string',        None),
            ('shiptype',      'uinteger',      '0'),
            ('shiptype_text', 'ignore',        None),
            ('to_bow',        'uinteger',      '0'),
            ('to_stern',      'uinteger',      '0'),
            ('to_port',       'uinteger',      '0'),
            ('to_starboard',  'uinteger',      '0'),
            ('epfd',          'uinteger',      '0'),
            ('epfd_text',     'ignore',        None),
            ('raim',          'boolean',       'false'),
            ('dte',           'uinteger',      '1'),
            ('assigned',      'boolean',       'false'),
        ),
    },
    {
        "initname": "json_ais20",
        "headers": ("AIS_HEADER",),
        "structname": "ais->type20",
        "fieldmap": (
            # fieldname       type             default
            ('offset1',       'uinteger',      '0'),
            ('number1',       'uinteger',      '0'),
            ('timeout1',      'uinteger',      '0'),
            ('increment1',    'uinteger',      '0'),
            ('offset2',       'uinteger',      '0'),
            ('number2',       'uinteger',      '0'),
            ('timeout2',      'uinteger',      '0'),
            ('increment2',    'uinteger',      '0'),
            ('offset3',       'uinteger',      '0'),
            ('number3',       'uinteger',      '0'),
            ('timeout3',      'uinteger',      '0'),
            ('increment3',    'uinteger',      '0'),
            ('offset4',       'uinteger',      '0'),
            ('number4',       'uinteger',      '0'),
            ('timeout4',      'uinteger',      '0'),
            ('increment4',    'uinteger',      '0'),
        ),
    },
    {
        "initname": "json_ais21",
        "headers": ("AIS_HEADER",),
        "structname": "ais->type21",
        "fieldmap": (
            # fieldname       type             default
            ('aid_type',      'uinteger',      '0'),
            ('aid_type_text', 'ignore',        None),
            ('name',          'string',        None),
            ('accuracy',      'boolean',       'false'),
            ('lon',           'integer',       'AIS_LON_NOT_AVAILABLE'),
            ('lat',           'integer',       'AIS_LAT_NOT_AVAILABLE'),
            ('to_bow',        'uinteger',      '0'),
            ('to_stern',      'uinteger',      '0'),
            ('to_port',       'uinteger',      '0'),
            ('to_starboard',  'uinteger',      '0'),
            ('epfd',          'uinteger',      '0'),
            ('epfd_text',     'ignore',        None),
            ('second',        'uinteger',      '0'),
            ('regional',      'uinteger',      '0'),
            ('off_position',  'boolean',       'false'),
            ('raim',          'boolean',       'false'),
            ('virtual_aid',   'boolean',       'false'),
        ),
    },
    {
        "initname": "json_ais22",
        "headers": ("AIS_HEADER",),
        "structname": "ais->type22",
        "fieldmap": (
            # fieldname       type             default
            ('channel_a',     'uinteger',      '0'),
            ('channel_b',     'uinteger',      '0'),
            ('txrx',          'uinteger',      '0'),
            ('power',         'boolean',       'false'),
            ('area.ne_lon',   'integer',       'AIS_GNS_LON_NOT_AVAILABLE'),
            ('area.ne_lat',   'integer',       'AIS_GNS_LAT_NOT_AVAILABLE'),
            ('area.sw_lon',   'integer',       'AIS_GNS_LON_NOT_AVAILABLE'),
            ('area.sw_lat',   'integer',       'AIS_GNS_LAT_NOT_AVAILABLE'),
            ('mmsi.dest1',    'uinteger',      '0'),
            ('mmsi.dest2',    'uinteger',      '0'),
            ('addressed',     'boolean',       'false'),
            ('band_a',        'boolean',       'false'),
            ('band_b',        'boolean',       'false'),
            ('zonesize',      'uinteger',      '0'),
        ),
    },
    {
        "initname": "json_ais23",
        "headers": ("AIS_HEADER",),
        "structname": "ais->type23",
        "fieldmap": (
            # fieldname       type             default
            ('ne_lon',        'integer',       'AIS_GNS_LON_NOT_AVAILABLE'),
            ('ne_lat',        'integer',       'AIS_GNS_LAT_NOT_AVAILABLE'),
            ('sw_lon',        'integer',       'AIS_GNS_LON_NOT_AVAILABLE'),
            ('sw_lat',        'integer',       'AIS_GNS_LAT_NOT_AVAILABLE'),
            ('stationtype',   'uinteger',      '0'),
            ('stationtype_text', 'ignore',     None),
            ('shiptype',      'uinteger',      '0'),
            ('shiptype_text', 'ignore',        None),
            ('txrx',          'uinteger',      '0'),
            ('interval',      'uinteger',      '0'),
            ('quiet',         'uinteger',      '0'),
        ),
    },
    {
        "initname": "json_ais24",
        "headers": ("AIS_HEADER",),
        "structname": "ais->type24",
        "fieldmap": (
            # fieldname             type             default
            ('shipname',          'string',        None),       # Part A
            ('shiptype',          'uinteger',      '0'),        # Part B
            ('shiptype_text',     'ignore',        None),
            ('vendorid',          'string',        None),       # Part B
            ('model',             'uinteger',      '0'),        # Part B
            ('serial',            'uinteger',      '0'),        # Part B
            ('callsign',          'string',        None),       # Part B
            ('mothership_mmsi',   'uinteger',      '0'),        # Part B
            ('dim.to_bow',        'uinteger',      '0'),        # Part B
            ('dim.to_stern',      'uinteger',      '0'),        # Part B
            ('dim.to_port',       'uinteger',      '0'),        # Part B
            ('dim.to_starboard',  'uinteger',      '0'),        # Part B
        ),
    },
    {
        "initname": "json_ais25",
        "headers": ("AIS_HEADER",),
        "structname": "ais->type25",
        "fieldmap": (
            # fieldname       type             default
            ('addressed',     'boolean',       'false'),
            ('structured',    'boolean',       'false'),
            ('dest_mmsi',     'uinteger',      '0'),
            ('app_id',        'uinteger',      '0'),
            ('data',          'string',        None),
        ),
        "stringbuffered": ("data",),
    },
    {
        "initname": "json_ais26",
        "headers": ("AIS_HEADER",),
        "structname": "ais->type26",
        "fieldmap": (
            # fieldname       type             default
            ('addressed',     'boolean',       'false'),
            ('structured',    'boolean',       'false'),
            ('dest_mmsi',     'uinteger',      '0'),
            ('app_id',        'uinteger',      '0'),
            ('data',          'string',        None),
            ('radio',         'uinteger',      '0'),
        ),
        "stringbuffered": ("data",),
    },
    {
        "initname": "json_ais27",
        "headers": ("AIS_HEADER",),
        "structname": "ais->type27",
        "fieldmap": (
            # fieldname   type        default
            ('status',   'uinteger', '0'),
            ('speed',    'uinteger', 'AIS_LONGRANGE_SPEED_NOT_AVAILABLE'),
            ('accuracy', 'boolean',  'false'),
            ('lon',      'integer',  'AIS_LONGRANGE_LON_NOT_AVAILABLE'),
            ('lat',      'integer',  'AIS_LONGRANGE_LAT_NOT_AVAILABLE'),
            ('course',   'uinteger', 'AIS_LONGRANGE_COURSE_NOT_AVAILABLE'),
            ('raim',     'boolean',  'false'),
            ('gnss',     'boolean',  'true'),
        ),
    },
)

# You should not need to modify anything below this line.


def generate(spec):
    report = ""
    leader = " " * 39
    initname = spec["initname"]
    # Utter storage declarations for any fields that are declared to be
    # stringbuffered. These will need to be postprocessed in json_ais_read().
    attributes = [t[0] for t in spec["fieldmap"]]
    for attr in spec.get("stringbuffered", []):
        if attr not in attributes:
            sys.stderr.write("buffered %s is not in base attributes of %s\n"
                             % (attr, initname))
            raise SystemExit(1)

        if attr not in outboard:
            report += "    char %s[JSON_VAL_MAX+1];\n" % attr
            outboard.append(attr)

    structname = spec["structname"]
    # If there are structarrays describing array subobjects, we need
    # to make a separate parse control initializer for each one.  The
    # attribute name is the name of the array; substructure and length
    # fieldnames must be given in the defaults part.
    for (attr, itype, arrayparts) in spec["fieldmap"]:
        if itype == 'array':
            (innerstruct, lengthfield, elements) = arrayparts
            report += ("    const struct json_attr_t %s_%s_subtype[] = {\n"
                       % (initname, attr))
            for (subattr, subitype, default) in elements:
                report += ('\t{"%s",%st_%s,%sSTRUCTOBJECT(struct %s, %s),\n'
                           % (subattr, " " * (14 - len(subattr)), subitype,
                              " " * (8 - len(subitype)), innerstruct, subattr))
                if subitype != "string":
                    report += (leader + ".dflt.%s = %s},\n"
                               % (subitype, default))
                elif default:
                    report += leader + ".len = %s},\n" % (default,)
                else:
                    sys.stderr.write(
                        "explicit length specification required\n")
                    raise SystemExit(1)
            report += """\
        {NULL}
    };
"""
    # Generate the main structure definition describing this parse.
    # It may have object subarrays.
    report += "    const struct json_attr_t %s[] = {\n" % initname
    if "headers" in spec:
        for header in spec["headers"]:
            report += '\t' + header + "\n"
    for (attr, itype, default) in spec["fieldmap"]:
        if itype == 'array':
            (innerstruct, lengthfield, elements) = default
            report += ('\t{"%s",%st_array,     '
                       'STRUCTARRAY(%s.%s, %s_%s_subtype, &%s.%s)},\n'
                       % (attr, " " * (14 - len(attr)), structname, attr,
                          initname, attr, structname, lengthfield))
        else:
            if itype == "string":
                deref = ""
            else:
                deref = "&"
            if attr in spec.get("stringbuffered", []):
                target = attr
            else:
                target = structname + "." + attr
            if "." in attr:
                attr = attr[attr.rfind(".") + 1:]
            if itype == 'ignore':
                report += '\t{"%s",   t_ignore},\n' % attr
                continue
            report += '\t{"%s",%st_%s,%s.addr.%s = %s%s,\n' % \
                (attr, " " * (14 - len(attr)), itype, " " * (10 - len(itype)),
                 itype, deref, target)
            if itype == "string":
                report += leader + ".len = sizeof(%s)},\n" % target
            else:
                report += leader + ".dflt.%s = %s},\n" % (itype, default)
    report += """\
        {NULL}
    };
"""
    print(report)


if __name__ == '__main__':
    try:
        # The --ais and --target= options are (required) placeholders.
        # In the future, this script will generate more different kinds
        # of code.
        (options, arguments) = getopt.getopt(sys.argv[1:], "",
                                             ["ais", "target="])
    except getopt.GetoptError as msg:
        print("jsongen.py: " + str(msg))
        raise SystemExit(1)

    spec = None
    target = None
    for (switch, val) in options:
        if switch == '--ais':
            spec = ais_specs
        elif switch == '--target':
            target = val

    if not target or not spec:
        print("jsongen.py: must specify type and target.")
        raise SystemExit(1)

    if target == 'parser':
        print("""/*
 * This is code generated by jsongen.py. Do not hand-hack it!
 */
 #define NITEMS(x) (int)(sizeof(x)/sizeof(x[0]))

""")
        outboard = []
        for description in spec:
            generate(description)
        print("""

/* Generated code ends. */
""")
# The following sets edit modes for GNU EMACS
# Local Variables:
# mode:python
# End:
