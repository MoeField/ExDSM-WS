$("#loginButton").on("click", function () {
    var pwd = $("#login input:eq(0)").val();

    $.ajax({
        //几个参数需要注意一下
        type: "POST",//方法类型
        url: "adminApi/adminLogin",//url
        //dataType: "text",//预期服务器返回的数据类型[xml,html,script,json,jsonp,text]
        data: {
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

    $("#查看用户信息").on("click", function () {
        var pwd = $("#login input:eq(0)").val();
        $.ajax({
            url: "/adminApi/adminGetUsrData",
            type: "POST",
            data: {
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

    $("#查看所有快递").on("click", function () {//by uuid
        var pwd = $("#login input:eq(0)").val();
        $.ajax({
            url: "/adminApi/adminGetPkgData",
            type: "POST",
            data: {
                "password": pwd,
            },
            dataType: "json",
            success: function (data) {
                /*这个方法里是ajax发送请求成功之后执行的代码*/
                console.log(data);
                showPackageData(data, "#pkgData");//数据展示
                alert("查询完毕");
            },
            error: function (msg) {
                alert("ajax连接异常：" + msg);
            }
        });
    }),

    $("#确认查询").on("click", function () {//by uuid
        var pwd = $("#login input:eq(0)").val();
        var pkgUid = $("#inquirePkg input:eq(0)").val();
        $.ajax({
            url: "/adminApi/checkPkgInUid",
            type: "POST",
            data: {
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

    $("#查看余额").on("click", function () {
        var pwd = $("#login input:eq(0)").val();
        $.ajax({
            url: "/adminApi/checkBallance",
            type: "POST",
            data: {
                "password": pwd
            },
            dataType: "json",
            success: function (data) {
                /*这个方法里是ajax发送请求成功之后执行的代码*/
                console.log(data);
                let strEnd = "";
                strEnd += "<p id='ballance'>"
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

    $("#确认修改").on("click", function () {
        var pwd = $("#login input:eq(0)").val();

        var npwd = $("#changePwd input:eq(0)").val();
        var npwdR = $("#changePwd input:eq(1)").val();

        if (npwd == npwdR) {
            $.ajax({
                url: "/adminApi/adminChangePwd",
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
        else {
            alert("两次密码不一致！");
        }
    });
//-----------------------------------------//

function showUsrData(data) {
    for (let i = 0; i < data.length; i++) {
        let strEnd = "";
        strEnd += "<h1>" + (i + 1).toString() + "</h1>";
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