// ==UserScript==
// @name         New Userscript
// @namespace    http://tampermonkey.net/
// @version      2024-03-13
// @description  try to take over the world!
// @author       You
// @match        https://jwk.lzu.edu.cn/academic/common/security/affairLogin.jsp
// @icon         https://www.google.com/s2/favicons?sz=64&domain=lzu.edu.cn
// @grant        none
// ==/UserScript==

(function() {
    'use strict';
    document.querySelector('body > form > div.content > div > div:nth-child(3) > input').value = '320210931221';
    document.querySelector('body > form > div.content > div > div:nth-child(4) > input').value = 'Wangxy_438439';
    // Your code here...
})();