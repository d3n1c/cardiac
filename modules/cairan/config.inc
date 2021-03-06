<?php
/* 
 *  Copyright (c) 2009 Denic Wibowo<denicwibowo@gmail.com>.
 *  All rights reserved.
 *  
 *  This program is free software; you can redistribute it and/or modify it 
 *  under the terms of the GNU General Public License as published by the 
 *  Free Software Foundation; either version 2 of the License, or 
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful, but 
 *  WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General 
 *  Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License along 
 *  with this program; if not, write to the Free Software Foundation, Inc., 
 *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *  
 *  config.php
 *  
 *  Created on Dec 18, 2009, 1:16:17 PM
 */

class cairanConfig extends config
{
    var $rdbms = 'mysql';
    var $dbcairan = array(
        'name' => 'layanan_kesehatan',
        'prefix' => '',
        'suffix' => '',
        'tbprefix' => '',
        'tbsuffix' => '',
        'host' => 'localhost',
        'user' => 'root',
        'passwd' => 'emmank'
    );
    var $hiddenfields = array(
        'id', 'inputer', 'inputtime', 'updated', 'perawatan'
    );
    var $typeoffields = array(
        'id' => 'hidden',
        'perawatan' => 'hidden',
        'tgl' => 'datetime',
        'kebiasaan_minum' => 'text',
        'jenis_minuman' => 'text',
        'turgor_kulit_elastis' => 'text',
        'mukosa_mulut_kering' => 'text',
        'keadaan_mata' => 'text',
        'pasien_edema' => 'text',
        'letak_edema' => 'text',
        'pasien_asites' => 'text',
        'asites' => 'text',
        'menggunakan_ngt' => 'text',
        'volume_ngt' => 'text',
        'mengalami_kelebihan_cairan' => 'text',
        'inputer' => 'system',
        'inputtime' => 'system',
        'updated' => 'system'
    );
    var $fieldsisarray = array(
        'diet', 'status_cairan'
    );
    var $reftable = array(
        'diet' => array('ref_present_risk_factor', 'risk_factor', 'id'),
        'status_cairan' => array('ref_present_risk_factor', 'risk_factor', 'id')
    );

    var $table_scheme = array(
        'cairan' => array(
            'id' => array(
                'type' => 'int(11)',
                'null' => 0,
                'key' => 'pri',
                'default' => NULL,
                'extra' => ''
            ),
            'perawatan' => array(
                'type' => 'int(11)',
                'null' => 0,
                'key' => '',
                'default' => NULL,
                'extra' => ''
            ),
            'tgl' => array(
                'type' => 'datetime',
                'null' => 0,
                'key' => '',
                'default' => NULL,
                'extra' => ''
            ),
            'kebiasaan_minum' => array(
                'type' => 'varchar(100)',
                'null' => 1,
                'key' => '',
                'default' => NULL,
                'extra' => ''
            ),
            'jenis_minuman' => array(
                'type' => 'varchar(100)',
                'null' => 1,
                'key' => '',
                'default' => NULL,
                'extra' => ''
            ),
            'turgor_kulit_elastis' => array(
                'type' => 'varchar(10)',
                'null' => 1,
                'key' => '',
                'default' => NULL,
                'extra' => ''
            ),
            'mukosa_mulut_kering' => array(
                'type' => 'varchar(10)',
                'null' => 1,
                'key' => '',
                'default' => NULL,
                'extra' => ''
            ),
            'keadaan_mata' => array(
                'type' => 'varchar(50)',
                'null' => 1,
                'key' => '',
                'default' => NULL,
                'extra' => ''
            ),
            'pasien_edema' => array(
                'type' => 'varchar(10)',
                'null' => 1,
                'key' => '',
                'default' => NULL,
                'extra' => ''
            ),
            'letak_edema' => array(
                'type' => 'varchar(10)',
                'null' => 1,
                'key' => '',
                'default' => NULL,
                'extra' => ''
            ),
            'pasien_asites' => array(
                'type' => 'varchar(10)',
                'null' => 1,
                'key' => '',
                'default' => NULL,
                'extra' => ''
            ),
            'asites' => array(
                'type' => 'varchar(10)',
                'null' => 1,
                'key' => '',
                'default' => NULL,
                'extra' => ''
            ),
            'menggunakan_ngt' => array(
                'type' => 'varchar(10)',
                'null' => 1,
                'key' => '',
                'default' => NULL,
                'extra' => ''
            ),
            'volume_ngt' => array(
                'type' => 'varchar(10)',
                'null' => 1,
                'key' => '',
                'default' => NULL,
                'extra' => ''
            ),
            'mengalami_kelebihan_cairan' => array(
                'type' => 'varchar(10)',
                'null' => 1,
                'key' => '',
                'default' => NULL,
                'extra' => ''
            ),
            'inputer' => array(
                'type' => 'int(11)',
                'null' => 0,
                'key' => '',
                'default' => NULL,
                'extra' => ''
            ),
            'inputtime' => array(
                'type' => 'datetime',
                'null' => 0,
                'key' => '',
                'default' => NULL,
                'extra' => ''
            ),
            'updated' => array(
                'type' => 'varchar(100)',
                'null' => 1,
                'key' => '',
                'default' => NULL,
                'extra' => ''
            )
        )
    );
}