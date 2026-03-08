intent GREET {
    name = call UserService.getName(user_id);
    reply "尊敬的 ${name}，您好。请问您有什么需求？";
}

intent QUERY_ORDER {
    require order_id4 "请提供您的订单号，方便我查询。";
    
    status = call OrderService.getStatus(order_id4);
    
    if (status == "SHIPPED") {
        reply "【V2】尊贵的会员，您的订单 ${order_id4} 已发货，正在急速配送中。";
    } else {
        reply "【V2】尊贵的会员，您的订单 ${order_id4} 已签收。";
    }
}