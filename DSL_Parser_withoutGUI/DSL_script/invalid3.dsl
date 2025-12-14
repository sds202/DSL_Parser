intent GREET_USER {
    name = call UserService.getName();
    reply "您好，${name}，欢迎来到我们的商城，需要我帮您找商品吗？";
}
