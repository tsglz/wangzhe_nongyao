// std::string waitForInput(Hero *hero, Hero *enemy)
// 


//     // ��һ���߳��еȴ��û�����
//     std::thread input_thread([&t, &input_mutex]()
//                              {
//         std::string input;
//         std::cout << "�������κ�������ֹͣ��ʱ��: ";
//         std::getline(std::cin, input); // �ȴ��û�����
//         // ������ɺ�ֹͣ��ʱ��
//         std::lock_guard<std::mutex> lock(input_mutex);
//         t.Stop();
//         return input; });

//     // ���̼߳���ִ�У��ȴ���ʱ�����
//     // ������ĳЩ�����£�����ϣ��������һ��ʱ�������ֹͣ��������
//     std::this_thread::sleep_for(std::chrono::seconds(3));
//     std::cout << "Stopping timer..." << std::endl;

//     // ��3���ֹͣ��ʱ���ĺ�������
//     // ���ﲻ����Ҫ���� Stop()����Ϊ����û������ˣ���ʱ���Ѿ�ֹͣ

//     // �ȴ������߳̽���
//     input_thread.join();

//     // �ȴ���ʱ�����ִ��
//     std::this_thread::sleep_for(std::chrono::seconds(5));
//     std::cout << "Function ends." << std::endl;
//     return input;
// }

// // // ������ִ�ж�ʱ����
// // t.StartTimer(1000, std::bind(EchoFunc, "hello world!"));
// // std::this_thread::sleep_for(std::chrono::seconds(4));
// // std::cout << "try to expire timer!" << std::endl;
// // t.Expire();

// // // ������ִ�ж�ʱ����
// // t.StartTimer(1000, std::bind(EchoFunc, "hello c++11!"));
// // std::this_thread::sleep_for(std::chrono::seconds(4));
// // std::cout << "try to expire timer!" << std::endl;
// // t.Expire();

// // std::this_thread::sleep_for(std::chrono::seconds(2));

// // ִֻ��һ�ζ�ʱ����
// // ͬ��
// // t.SyncWait(1000, EchoFunc, "hello world!");
// // �첽

// // std::this_thread::sleep_for(std::chrono::seconds(2));
