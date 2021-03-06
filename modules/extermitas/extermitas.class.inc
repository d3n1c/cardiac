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
 *  extermitasclass.php
 *  
 *  Created on Oct 6, 2009, 11:56:59 AM
 */

require_once MODULES_DIR . DS . 'extermitas' . DS . 'config.inc';

class extermitasModule extends mainModule
{
    var $title = 'extermitas module';
    var $description = '';

    function menu(){
        $items['ref_extermitas_inspections'] = array(
            'title' => __t('extermitas_inspections'),
            'description' => __t('inspections reference form for extermitas'),
            'path' => '/reference/extermitas_inspections',
            'exec' => 'ref_inspections_view',
            'weight' => '0',
            'user_required' => NULL
        );
        $items['ref_extermitas_inspections_detail'] = array(
            'title' => __t('detil extermitas_inspections'),
            'description' => __t('inspections reference detail for extermitas'),
            'path' => '/reference/extermitas_inspections/detail',
            'exec' => 'ref_inspections_detail',
            'weight' => '0',
            'user_required' => NULL
        );
        $items['ref_extermitas_inspections_form'] = array(
            'title' => __t('extermitas_inspections form'),
            'description' => __t('inspections reference form for extermitas'),
            'path' => '/reference/extermitas_inspections/form',
            'exec' => 'ref_inspections_form',
            'weight' => '0',
            'user_required' => 'reference'
        );
        $items['ref_extermitas_inspections_form_submit'] = array(
            'title' => __t('extermitas_inspections form'),
            'description' => __t('Execute inspections reference form for extermitas'),
            'path' => '/reference/extermitas_inspections/form_submit',
            'exec' => 'ref_inspections_form_submit',
            'weight' => '0',
            'user_required' => 'reference'
        );
        $items['ref_extermitas_inspections_edit'] = array(
            'title' => __t('extermitas_inspections edit'),
            'description' => __t('Editing inspections reference form for extermitas'),
            'path' => '/reference/extermitas_inspections/edit',
            'exec' => 'ref_inspections_edit',
            'weight' => '0',
            'user_required' => 'reference'
        );
        $items['ref_extermitas_inspections_drop'] = array(
            'title' => __t('extermitas_inspections drop'),
            'description' => __t('Remove inspections reference form for extermitas'),
            'path' => '/reference/extermitas_inspections/drop',
            'exec' => 'ref_inspections_drop',
            'weight' => '0',
            'user_required' => 'reference'
        );
        return $items;
    }

    function ref_inspections_view(){
        $result = array();
        $result['type'] = 'table';
        $result['title'] = __t('Referensi inspeksi extermitas');
        $result['description'] = __t('Referensi pilihan inspeksi extermitas pasien');
        $result['addmenu'] = array(
            'title' => __t('add reference'),
            'action' => '/reference/extermitas_inspections/form',
            'position' => 'top',
            'user_required' => 'reference'
        );
        $result['header'] = array(
            array(
                'field' => 'none',
                'caption' => __t('no'),
                'width' => '5%',
                'align' => 'right'
            ),
            array(
                'field' => 'inspections',
                'caption' => __t('keterangan'),
                'align' => 'left'
            )
        );
        $this->query->connect();
        $sql = $this->query->getSelect(
            array(),
            array('ref_extermitas_inspections'),
            NULL,
            'inspections'
        );
        $query = $this->query->conn->Execute($sql); unset($sql);
        $this->query->close();
        if($query->_numOfRows > 0){
            for($i=0; $i<$query->_numOfRows; $i++){
                $result['data'][$i] = $query->fields;
                $result['data'][$i]['inspections'] = ucwords($query->fields['inspections']);
                $result['data'][$i]['goto'] = '/reference/extermitas_inspections/detail/' . $query->fields['id'];
                $query->MoveNext();
            }
        }
        return $result;
    }

    function ref_inspections_form(){
        if ($this->__check_caches() === TRUE){
            $vcache = $this->__read_form_cache();
        }
//        echo '<pre>'; print_r($vcache); echo '</pre>';
        $form['group'] = array(
            '#type' => 'fieldset',
            '#id' => 'group',
            '#title' => __t('add extermitas_inspections'),
            '#collapsible' => TRUE,
            '#collapsed' => FALSE,
            '#focused_item' => 'inspections',
            '#weight' => -3,
            '#action' => '/reference/extermitas_inspections/form_submit',
            '#error' => isset($vcache['error']) ? $vcache['error'] : FALSE
        );
        $this->query->connect();
        $sql = $this->query->getDescribe('ref_extermitas_inspections');
        $query = $this->query->conn->Execute($sql); unset($sql);
        $this->query->close();
        for($i=0; $i<$query->_numOfRows; $i++){
            if(!in_array($query->fields['Field'], array('id'))){
                $form['group'][$query->fields['Field']] = array(
                    '#type' => 'text',
                    '#title' => __t($query->fields['Field']),
                    '#value' => isset($vcache[$query->fields['Field']]) ? $vcache[$query->fields['Field']] : ($query->fields['Field'] == 'id' ? $_POST['id'] : ''),
                    '#error' => isset($vcache['blank']) && in_array($query->fields['Field'], $vcache['blank']) ? 1 : 0
                );
            }
            $query->MoveNext();
        } unset($query);
        $form['group']['submit'] = array(
            '#type' => 'submit',
            '#title' => '&nbsp;',
            '#value' => __t('input')
        );
        return $form;
    }

    function ref_inspections_form_submit(){
//        if($_POST['id'] != ''){
            $dump = $this->__write_form_cache();
            foreach($dump as $key => $value){
                if($value == ''){
                    $this->__write_custom_cache(
                        array('error' => __t('Data kurang lengkap di kolom <strong>"') . __t($key) . '"</strong>', 1)
                    );
                    redirect_to('/reference/extermitas_inspections/form');
                    exit();
                }
                if($key != 'blank' && $key != 'submit'){
                    $thevalue[$key] = $value;
                }
            } unset($dump);
            $thevalue['id'] = $this->__get_id_insert_value('ref_extermitas_inspections', 'id', $this->query);
//        echo '<pre>'; print_r($thevalue); echo '</pre>'; exit();
            $this->query->connect();
            $sql = $this->query->saveData(
                'ref_extermitas_inspections',
                $thevalue
            );
            $this->query->conn->Execute($sql); unset($sql);
            $this->query->close();
            unset($thevalue);
            redirect_to('/reference/extermitas_inspections');
//        } else {
//            redirect_to('/reference/extermitas_inspections/form');
//        }
    }

    function ref_inspections_detail(){
        $dump = explode('/', trim(preg_replace('/^\//','',$_GET['q'])));
        if(count($dump) > 4){
            $update = $dump[4];
        }
        $keyid = $dump[3]; unset($dump);
        $dropable = $this->__is_dropable($keyid, 'inspections', 'extermitas', $this->query);
        $result = array();
        $result['type'] = 'items_detail';
        $result['title'] = __t('detil referensi inspections');
        $result['description'] = __t('informasi detil referensi inspections yang terpilih');
        $result['id'] = $keyid;
        $result['update_access'] = 'reference';
        $result['dropable'] = $dropable !== FALSE ? '/reference/extermitas_inspections/drop' : '0';
        unset($dropable);
        $this->query->connect();
        $sql = $this->query->getSelect(
            array('id', 'inspections'),
            array('ref_extermitas_inspections'),
            array(
                array('&&', "id=" . $keyid)
            )
        );
        $query = $this->query->conn->Execute($sql); unset($sql);
        $this->query->close();
        if(isset($update)){
            $showsubmit = array('textarea', 'date');
        }
        foreach($query->fields as $key => $value){
            $result['data'][$key] = array(
                'key' => __t($key),
                'value' => $value,
                'link' => '/reference/extermitas_inspections/detail/' . $keyid . '/' . $key,
                'hide' => in_array($key, $this->config->hiddenfields) ? 1 : 0
            );
            if(isset($update) && $key == $update){
                $result['data'][$key]['form'] = array(
                    'detail' => array(
                        '#type' => 'fieldset',
                        '#title' => 'hidden',
                        '#action' => '/reference/extermitas_inspections/edit/',
                        'id' => array(
                            '#type' => 'hidden',
                            '#value' => $keyid
                        ),
                        $key => array(
                            '#type' => 'text',
                            '#value' => $value,
                            '#title' => 'hidden',
                            '#size' => $this->formtype_fields[$key] == 'select' ? 1 : 20,
                            '#extra' => $this->formtype_fields[$key] == 'select' ? 'onchange="Javascript:this.form.submit()"' : ''
                        )
                    )
                );
                if(in_array($result['data'][$key]['form']['detail'][$key]['#type'], $showsubmit)){
                    $result['data'][$key]['form']['detail'][$key]['submit'] = array(
                        '#type' => 'submit',
                        '#value' => 'submit',
                        '#title' => 'hidden'
                    );
                }
            }
        } unset($query, $keyid);
//        echo '<pre>'; print_r($result); echo '</pre>';
        return $result;
    }

    function ref_inspections_edit(){
        foreach($_POST as $key => $value){
            if($key != 'id'){
                if(in_array($key, $this->__get_data_fields('ref_extermitas_inspections', $this->query))){
                    $this->query->connect();
                    $sql = $this->query->updateData(
                        'ref_extermitas_inspections',
                        array(
                            $key => $value
                        ),
                        array(
                            array('&&', "id=" . $_POST['id'])
                        )
                    );
                    $this->query->conn->Execute($sql); unset($sql);
                    $this->query->close();
                }
            }
        }
        redirect_to('/reference/extermitas_inspections/detail/' . $_POST['id']);
    }

    function ref_inspections_drop(){
        if($this->__is_dropable($_POST['id'], 'inspections', 'extermitas', $this->query) !== FALSE){
            $this->query->connect();
            $sql = $this->query->setDelete(
                'ref_extermitas_inspections',
                array(
                    array('&&', "id=" . $_POST['id'])
                )
            );
            $this->query->conn->Execute($sql); unset($sql);
            $this->query->close();
        }
        redirect_to('/reference/extermitas_inspections');
    }

    function __get_refs($fields, $sort=NULL){
        $result = array();
        $sql = $this->query->getSelect(
            array(),
            array($this->config->reftable[$fields][0]),
            NULL,
            (!is_null($sort) ? $sort . ' asc' : 'id asc')
        );
        $this->query->connect();
        $query = $this->query->conn->Execute($sql); unset($sql);
        $this->query->close();
        for($i=0; $i<$query->_numOfRows; $i++){
            $result[$query->fields['id']] = $query->fields[$this->config->reftable[$fields][1]];
            $query->MoveNext();
        }
        return $result;
    }

    function cardio_menu(){
        $this->sync_scheme('extermitas', $this->query);
        $result = array();
        $result['#title'] = __t('Ekstermitas');
        $result['#tpl'] = MODULES_DIR . DS . 'extermitas' . DS . 'extermitas.tpl';
        $datafields = $this->__get_data_fields('extermitas', $this->query);
        if (count($this->config->free_val) > 0){
            $vcache = $this->config->free_val;
            $sql = $this->query->getSelect(
                array(),
                array('extermitas'),
                array(
                    array('&&', "id=" . $vcache['id'])
                )
            ); unset($vcache);
            $this->query->connect();
            $getit = $this->query->conn->Execute($sql); unset($sql);
            $this->query->close();
            if($getit->_numOfRows > 0){
                foreach($getit->fields as $key => $value){
                    $vcache[$key] = $value;
                }
            }
        }
        foreach($datafields as $key => $value){
            $result['datafields'][$value] = array(
                'title' => __t($value),
                'type' => $this->config->typeoffields[$value],
                'value' => isset($vcache[$value]) ? $vcache[$value] : ''
            );
            if(in_array($value, $this->config->fieldsisarray)){
                $result['datafields'][$value]['theref'] = $this->__get_refs($value);
            } elseif($this->config->typeoffields[$value] == 'datetime'){
                $result['datafields'][$value]['theref'] = $this->nama_bulan;
                $result['datafields'][$value]['timenow'] = $this->config->time;
            } else {
                $result['datafields'][$value]['size'] = 6;
            }
            $result['datafields'][$value]['readonly'] = isset($this->config->free_val['readonly']) ? true : false;
        }
        return $result;
    }

    function cardio_submit(){
        $thefields = $this->__get_data_fields('extermitas', $this->query);
        foreach($this->config->free_val as $key => $value){
            if(in_array($key, $thefields)){
                if($key == 'inspections'){
                    if(count($value) > 0){
                        $value = implode(',', $value);
                    }
                }
                $thevalue[$key] = $value;
            }
        } unset($thefields);
        if($_POST['id'] != ''){
            unset($thevalue['id']);
            $opr = 'update';
            $strid = array('id', $_POST['id']);
        } else {
            $opr = 'insert';
            $strid = array('id', $thevalue['id']);
        }
        $this->__exec_db_ops(
            $this->query,
            'extermitas',
            $opr,
            $strid,
            $thevalue
        );
        unset($thevalue, $opr, $strid);
    }


}