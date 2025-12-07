intent GREET {
    reply "尊敬的 ${name}，您好。请问您有什么需求？";
}

intent QUERY_ORDER {
    require order_id "请提供您的订单号，方便我查询。";
    
    status = call OrderService.getStatus(order_id);
    
    if (status == "SHIPPED") {
        reply "您的订单 ${order_id} 已发货，正在配送中。";
    } else if (status == "DELIVERED") {
        reply "您的订单 ${order_id} 已签收。";
    } else {
        reply "当前状态?";
    }
}

intent REFUND {
    require order_id "请问您要退款哪个订单？";
    require reason "能告诉我退款原因吗？";
    
    result = call OrderService.applyRefund(order_id, reason);
    
    if (result == "SUCCESS") {
        reply "退款申请已提交。";
    } else {
        reply "申请失败。";
    }
}