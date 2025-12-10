intent GREET_USER {
    name = call UserService.getName(user_id);
    reply "您好，${name}，欢迎来到我们的商城，需要我帮您找商品吗？";
}

intent PRODUCT_STOCK_QUERY {
    require product_id "请提供您要查询的商品编号。";

    stock = call InventoryService.getStock(product_id);

    if (stock > 0) {
        reply "商品 ${product_id} 目前库存为 ${stock} 件，可正常购买。";
    } else {
        reply "抱歉，商品 ${product_id} 暂时缺货。";
    }
}

intent APPLY_COUPON {
    require coupon_code "请告诉我您的优惠券代码。";

    result = call CouponService.apply(coupon_code, user_id);

    if (result == "VALID") {
        reply "优惠券已成功使用！结算时会自动为您减免金额。";
    } else if (result == "EXPIRED") {
        reply "该优惠券已过期。";
    } else {
        reply "优惠券无效，请确认后再试。";
    }
}

intent CONSULT_PROMOTION {
    promo = call PromotionService.getTodayPromo();

    if (promo == "NONE") {
        reply "今天暂时没有活动，但明天可能会有哦。";
    } else {
        reply "今日活动为：${promo}。";
    }
}
