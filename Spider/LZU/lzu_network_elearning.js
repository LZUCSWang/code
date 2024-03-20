// ==UserScript==
// @name         New Userscript
// @namespace    http://tampermonkey.net/
// @version      2024-03-10
// @description  try to take over the world!
// @author       You
// @match        http://10.10.0.166/srun_portal_pc?ac_id=2&nasip=10.6.0.16&theme=lzu*
// @icon         https://www.google.com/s2/favicons?sz=64&domain=0.166
// @grant        none
// ==/UserScript==

setTimeout(function () {
        'use strict';
        // var emailclick = document.getElementById('email');
        // 通过seletor找
        var emailclick = document.querySelector('body > div.login-panel.active > div.tab-container > div:nth-child(2)');
        emailclick.click();
        var domain_select = document.querySelector('#domain');
        var elearningOption = document.querySelector('#domain > option:nth-child(2)');
        elearningOption.selected = true;
        domain_select.click();
        var passwd = document.querySelector('#password');
        passwd.value="Wangxy_438439";
        document.querySelector('#login').click();
}, 1000);