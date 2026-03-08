intent GREET {
    name = call UserService.getName(user_id;
    reply "尊敬的 ${name}，您好。请问您有什么需求？";
}