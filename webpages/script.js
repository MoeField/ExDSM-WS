$("#regButton").on("click", function () {
    var UsrName = $("#register input:eq(0)").val();
    var RealName = $("#register input:eq(1)").val();
    var pwd = $("#register input:eq(2)").val();
    var tel = $("#register input:eq(3)").val();
    var address = $("#register input:eq(4)").val();
    $.ajax({
        //几个参数需要注意一下
        type: "POST",//方法类型
        url: "api/regist",//url
        //dataType: "text",//预期服务器返回的数据类型[xml,html,script,json,jsonp,text]
        data: {
            "usrName": UsrName,
            "password": pwd,
            "realName": RealName,
            "tel": tel,
            "address": address,
        },
        success: function (response, status, xhr) {
            console.log(response);	//服务器返回的信息
            console.log(status);	//服务器返回的信息
            console.log(xhr.status);	//状态码,   要看其他的直接 输出 xhr 就行
            console.log(xhr.getAllResponseHeaders()); //响应头部
            alert("注册成功！");
        },
        error: function (status, errorThrown) {
            console.log(status);
            alert("注册失败，用户名已被占用！" + errorThrown);
        }
    });
    return false;
}),

    $("#loginButton").on("click", function () {
        var UsrName = $("#login input:eq(0)").val();
        var pwd = $("#login input:eq(1)").val();

        $.ajax({
            //几个参数需要注意一下
            type: "POST",//方法类型
            url: "api/login",//url
            //dataType: "text",//预期服务器返回的数据类型[xml,html,script,json,jsonp,text]
            data: {
                "usrName": UsrName,
                "password": pwd
            },
            success: function (response, status, xhr) {
                console.log(response);	//服务器返回的信息
                console.log(status);	//服务器返回的信息
                console.log(xhr.status);	//状态码,   要看其他的直接 输出 xhr 就行
                console.log(xhr.getAllResponseHeaders()); //响应头部
                alert("登录成功！");
            },
            error: function (status, errorThrown) {
                console.log(status);
                alert("请检查用户名或密码！" + errorThrown);
            }
        });
        return false;
    }),

    $("#收包裹").on("click", function () {
        var UsrName = $("#login input:eq(0)").val();
        var pwd = $("#login input:eq(1)").val();
        $.ajax({
            url: "/api/checkRcv",
            type: "POST",
            data: {
                "usrName": UsrName,
                "password": pwd
            },
            dataType: "json",
            success: function (data) {
                /*这个方法里是ajax发送请求成功之后执行的代码*/
                console.log(data);
                showPackageData(data, "#RcvPkg");//数据展示
                alert("查询完毕！");
            },
            error: function (msg) {
                alert("ajax连接异常：" + msg);
            }
        });
    }),

    $("#寄包裹").on("click", function () {
        var UsrName = $("#login input:eq(0)").val();
        var pwd = $("#login input:eq(1)").val();
        $.ajax({
            url: "/api/checkSent",
            type: "POST",
            data: {
                "usrName": UsrName,
                "password": pwd
            },
            dataType: "json",
            success: function (data) {
                /*这个方法里是ajax发送请求成功之后执行的代码*/
                console.log(data);
                showPackageData(data, "#SentPkg");//数据展示
                alert("查询完毕！");
            },
            error: function (msg) {
                alert("ajax连接异常：" + msg);
            }
        });
    }),

    $("#确认收货").on("click", function () {
        var UsrName = $("#login input:eq(0)").val();
        var pwd = $("#login input:eq(1)").val();
        var pkgUid = $("#receiption input:eq(0)").val();
        $.ajax({
            url: "/api/receiption",
            type: "POST",
            data: {
                "usrName": UsrName,
                "password": pwd,
                "uuid" : pkgUid
            },
            success: function (data) {
                /*这个方法里是ajax发送请求成功之后执行的代码*/
                console.log(data);
            },
            error: function (msg) {
                alert("您可能已经签收过了，请刷新页面" + msg);
            }
        });
    }),

    $("#确认发货").on("click", function () {
        var UsrName = $("#login input:eq(0)").val();
        var pwd = $("#login input:eq(1)").val();

        var u = $("#send input:eq(0)").val();
        var d = $("#send input:eq(1)").val();
        var a = $("#send input:eq(2)").val();
        var t = $("#send input:eq(3)").val();

        $.ajax({
            url: "/api/sendPkg",
            type: "POST",
            data: {
                "usrName": UsrName,
                "password": pwd,
                "to":u,
                "type":t,
                "amount":a,
                "describe":d
            },
            success: function (response, status, xhr) {
                console.log(response);	//服务器返回的信息
                console.log(status);	//服务器返回的信息
                console.log(xhr.status);	//状态码,   要看其他的直接 输出 xhr 就行
                console.log(xhr.getAllResponseHeaders()); //响应头部
                alert("发货成功！");
            },
            error: function (status, errorThrown) {
                console.log(status);
                alert("余额不足/收件人不存在" + errorThrown);
            }
        });
    }),

    $("#查询").on("click", function () {//by uuid
        var UsrName = $("#login input:eq(0)").val();
        var pwd = $("#login input:eq(1)").val();
        var pkgUid = $("#inquirePkg input:eq(0)").val();
        $.ajax({
            url: "/api/checkPkgInUid",
            type: "POST",
            data: {
                "usrName": UsrName,
                "password": pwd,
                "uuid": pkgUid
            },
            dataType: "json",
            success: function (data) {
                /*这个方法里是ajax发送请求成功之后执行的代码*/
                console.log(data);
                showPackageData(data, "#InqPkg");//数据展示
                alert("查询完毕");
            },
            error: function (msg) {
                alert("ajax连接异常：" + msg);
            }
        });
    }),

    $("#我的钱包").on("click", function () {
        var UsrName = $("#login input:eq(0)").val();
        var pwd = $("#login input:eq(1)").val();
        $.ajax({
            url: "/api/getBallance",
            type: "POST",
            data: {
                "usrName": UsrName,
                "password": pwd
            },
            dataType: "json",
            success: function (data) {
                /*这个方法里是ajax发送请求成功之后执行的代码*/
                console.log(data);
                let strEnd="";
                strEnd +="<p id='ballance'>"
                    + data.ballance 
                    + "</p>";
                $("#ballance").append(strEnd);
            },
            error: function (status, errorThrown) {
                console.log(status);
                alert("ajax连接异常：" + errorThrown);
            }
        });
    }),

    $("#确认充值").on("click", function () {
        var UsrName = $("#login input:eq(0)").val();
        var pwd = $("#login input:eq(1)").val();
        var amount = $("#charge input:eq(0)").val();
        $.ajax({
            url: "/api/charge",
            type: "POST",
            data: {
                "usrName": UsrName,
                "password": pwd,
                "amount": amount
            },
            success: function (response, status, xhr) {
                console.log(response);	//服务器返回的信息
                console.log(status);	//服务器返回的信息
                console.log(xhr.status);	//状态码,   要看其他的直接 输出 xhr 就行
                console.log(xhr.getAllResponseHeaders()); //响应头部
                alert("充值成功！");
            },
            error: function (status, errorThrown) {
                console.log(status);
                alert("请检查用户名或密码！" + errorThrown);
            }
        });
    }),

    $("#我的账户").on("click", function () {
        var UsrName = $("#login input:eq(0)").val();
        var pwd = $("#login input:eq(1)").val();
        $.ajax({
            url: "/api/getUsrData",
            type: "POST",
            data: {
                "usrName": UsrName,
                "password": pwd
            },
            dataType: "json",
            success: function (data) {
                /*这个方法里是ajax发送请求成功之后执行的代码*/
                console.log(data);
                showUsrData(data);//数据展示
            },
            error: function (msg) {
                alert("ajax连接异常：" + msg);
            }
        });
    }),


    $("#确认修改").on("click", function () {
        var UsrName = $("#login input:eq(0)").val();
        var pwd = $("#login input:eq(1)").val();

        var npwd = $("#changePwd input:eq(0)").val();
        var npwdR = $("#changePwd input:eq(1)").val();

        if (npwd == npwdR){
        $.ajax({
            url: "/api/changePwd",
            type: "POST",
            data: {
                "usrName": UsrName,
                "password": pwd,
                "newPassword": npwd
            },
            success: function () {
                /*这个方法里是ajax发送请求成功之后执行的代码*/
                alert("请重新登陆！" + msg);
                location.reload();
            },
            error: function (msg) {
                alert("ajax连接异常：" + msg);
            }
        });
        }
        else{
            alert("两次密码不一致！");
        }
    });

//-----------------------------------------//

function showUsrData(data) {
    for (let i = 0; i < data.length; i++) {
        let strEnd = "";
        //strEnd += "<h1>" + (i + 1).toString() + "</h1>";
        strEnd += "<p class='firstP'><span class='title'>用户名：</span> <span>"
            + data[i].usrname
            + "</span></p> <div class='row'>"
            + "<p class='title'>密码：</p><p>"
            + data[i].pwd
            + "</p><p class='title'>真实姓名：</p><p>"
            + data[i].realName
            + "</p><p class='title'>地址：</p><p>"
            + data[i].address
            + "</p><p class='title'>电话：</p><p>"
            + data[i].tel
            + "</p><p class='title'>余额：</p><p>"
            + data[i].ballance
            + "</p><p class='title'>识别码：</p><p>"
            + data[i].uuid
            + "</p> </div> ";
        if (i != data.length - 1) {
            strEnd += "<hr class='hr'/>";
        }
        $("#accData").append(strEnd);
    }
}

function showPackageData(data, str_where) {
    for (let i = 0; i < data.length; i++) {
        let strEnd = "";
        strEnd += "<h1>" + (i + 1).toString() + "</h1>"
            + "<p class='firstP'><span class='title'>物流单号：</span> <span>"
            + data[i].UUID
            + "</span></p> <div class='row'>"
            + "<p class='title'>发件人：</p><p>"
            + data[i].from
            + "</p><p class='title'>收件人：</p><p>"
            + data[i].to
            + "</p><p class='title'>发件地址：</p><p>"
            + data[i].fAddr
            + "</p><p class='title'>收件地址：</p><p>"
            + data[i].tAddr
            + "</p><p class='title'>物品类别（2:书, 5:普通, 8:易碎）：</p><p>"
            + data[i].type
            + "</p><p class='title'>物品描述：</p><p>"
            + data[i].description
            + "</p><p class='title'>签收状态（0为未签收，1为已签收）：</p><p>"
            + data[i].status
            + "</p><p class='title'>发件时间：</p><p>"
            + data[i].sendTime
            + "</p><p class='title'>收件时间：</p><p>"
            + data[i].rcvTime
            + "</p> </div> ";
        if (i != data.length - 1) {
            strEnd += "<hr class='hr'/>";
        }
        $(str_where).append(strEnd);
    }
}

function getQueryVariable(variable) {
    var query = window.location.search.substring(1);
    var vars = query.split("&");
    for (var i = 0; i < vars.length; i++) {
        var pair = vars[i].split("=");
        if (pair[0] == variable) { return pair[1]; }
    }
    return (false);
}