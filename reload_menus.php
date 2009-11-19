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
 *  reload_menus.php
 *  
 *  Created on Nov 18, 2009, 9:50:27 AM
 */

require 'includes' . DIRECTORY_SEPARATOR . 'constant.inc';
require INCLUDES_DIR . DS . 'defaultvars.inc';

//function __get_menu_sights(){
//    global $configs;
//    $result = array();
//    foreach($configs->menu_sights as $key => $value){
//        $result[$key] = $value;
//    }
//    return $result;
//}
//
//function get_active_modules(){
//    global $systemquery, $configs;
//    $result = array();
//    $sql = $systemquery->getSelect(
//        array(),
//        array('modules'),
//        NULL,
//        'module'
//    );
//    $systemquery->connect();
//    $query = $systemquery->conn->Execute($sql); unset($sql);
//    $systemquery->close();
//    for($i=0; $i<$query->_numOfRows; $i++){
//        $result[] = $query->fields['module'];
//        $query->MoveNext();
//    } unset($query);
//    return $result;
//}

$allelements = array();
$dumpsights = __get_menu_sights();
foreach($dumpsights as $key=>$value){
    $allelements[$key] = $value;
    $allelements[$key]['source'] = 'configs';
} unset($dumpsights);
$modules = get_active_modules();
foreach($modules as $key=>$value){
    require MODULES_DIR . DS . $value . DS . $value . '.module';
    $menu_lists = ${$value . '_exec'}->menu();
    foreach($menu_lists as $ke=>$val){
        $allelements[$ke] = $val;
        $allelements[$ke]['module'] = $value;
        $allelements[$ke]['source'] = 'modules';
    } unset($menu_lists);
} unset($modules);
foreach ($allelements as $key => $value){
    $sql = $systemquery->getSelect(
        array('id'),
        'menus',
        array(
            array('&&', "id=" . $key)
        )
    );
    $systemquery->connect();
    $getexist = $systemquery->conn->Execute($sql); unset($sql);
    $systemquery->close();
    if($getexist->_numOfRows < 1){
        $value['id'] = $key;
        $sql = $systemquery->saveData(
            'menus',
            $value
        ); unset($value['id']);
    } else {
        $sql = $systemquery->updateData(
            'menus',
            $value,
            array(
                array('&&', "id=" . $key)
            )
        );
    }
    $systemquery->connect();
    $systemquery->conn->Execute($sql); unset($sql);
    $systemquery->close();
}

echo "done\n";

?>