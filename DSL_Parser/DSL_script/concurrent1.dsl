intent GREET {
    name = call UserService.getName(user_id);
    reply "尊敬的 ${name}，您好。请问您有什么需求？";
}

intent QUERY_ORDER {
    require order_id "请提供您的订单号，方便我查询。";
    
    status = call OrderService.getStatus(order_id);
    
    if (status == "SHIPPED") {
        reply "【V1】您的订单 ${order_id} 已发货，正在配送中。";
    } else {
        reply "【V1】您的订单 ${order_id} 已签收。";
    }
}