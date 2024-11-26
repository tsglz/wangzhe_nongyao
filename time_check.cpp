// std::string waitForInput(Hero *hero, Hero *enemy)
// 


//     // 在一个线程中等待用户输入
//     std::thread input_thread([&t, &input_mutex]()
//                              {
//         std::string input;
//         std::cout << "请输入任何内容以停止定时器: ";
//         std::getline(std::cin, input); // 等待用户输入
//         // 输入完成后停止定时器
//         std::lock_guard<std::mutex> lock(input_mutex);
//         t.Stop();
//         return input; });

//     // 主线程继续执行，等待定时器完成
//     // 假设在某些条件下，我们希望在运行一段时间后立即停止后续任务
//     std::this_thread::sleep_for(std::chrono::seconds(3));
//     std::cout << "Stopping timer..." << std::endl;

//     // 在3秒后停止定时器的后续操作
//     // 这里不再需要调用 Stop()，因为如果用户输入了，定时器已经停止

//     // 等待输入线程结束
//     input_thread.join();

//     // 等待定时器完成执行
//     std::this_thread::sleep_for(std::chrono::seconds(5));
//     std::cout << "Function ends." << std::endl;
//     return input;
// }

// // // 周期性执行定时任务
// // t.StartTimer(1000, std::bind(EchoFunc, "hello world!"));
// // std::this_thread::sleep_for(std::chrono::seconds(4));
// // std::cout << "try to expire timer!" << std::endl;
// // t.Expire();

// // // 周期性执行定时任务
// // t.StartTimer(1000, std::bind(EchoFunc, "hello c++11!"));
// // std::this_thread::sleep_for(std::chrono::seconds(4));
// // std::cout << "try to expire timer!" << std::endl;
// // t.Expire();

// // std::this_thread::sleep_for(std::chrono::seconds(2));

// // 只执行一次定时任务
// // 同步
// // t.SyncWait(1000, EchoFunc, "hello world!");
// // 异步

// // std::this_thread::sleep_for(std::chrono::seconds(2));
