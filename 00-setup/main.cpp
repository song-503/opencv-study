// RAW 이미지 뷰어 — OpenCV 개발환경(컴파일·링크·실행) 동작 확인용
// 사용법: TestViewer.exe <input.raw> <WIDTH> <HEIGHT>
//   헤더 없는 8비트 그레이스케일 RAW 파일을 읽어 화면에 표시한다.

#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// 문자열 → 양의 정수 변환. 숫자가 아니거나, 뒤에 문자가 붙거나, 0 이하면 예외
static int parsePositiveInt(const std::string& s, const char* name)
{
    size_t pos = 0;
    int value = std::stoi(s, &pos);  // 숫자가 아니면 invalid_argument, 범위 초과면 out_of_range
    if (pos != s.size())
        throw std::invalid_argument(std::string(name) + " has trailing characters: " + s);
    if (value <= 0)
        throw std::invalid_argument(std::string(name) + " must be positive: " + s);
    return value;
}

int main(int argc, char* argv[])
{
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <input.raw> <WIDTH> <HEIGHT>\n";
        return 1;
    }

    try {
        const int width  = parsePositiveInt(argv[2], "WIDTH");
        const int height = parsePositiveInt(argv[3], "HEIGHT");

        // size_t로 곱해서 int 오버플로 방지
        const size_t expected = static_cast<size_t>(width) * static_cast<size_t>(height);

        // ios::ate → 파일 끝에서 열어 tellg()로 바로 크기 확인
        std::ifstream input(argv[1], std::ios::binary | std::ios::ate);
        if (!input)
            throw std::runtime_error(std::string("cannot open file: ") + argv[1]);

        const std::streamoff fileSize = input.tellg();
        if (fileSize < 0 || static_cast<size_t>(fileSize) != expected)
            throw std::runtime_error("size mismatch: file is " + std::to_string(fileSize) +
                                     " bytes, expected " + std::to_string(expected) +
                                     " (" + std::to_string(width) + " x " + std::to_string(height) + ")");

        input.seekg(0, std::ios::beg);
        std::vector<unsigned char> pixels(expected);
        if (!input.read(reinterpret_cast<char*>(pixels.data()),
                        static_cast<std::streamsize>(pixels.size())))
            throw std::runtime_error("failed to read RAW data");

        // 주의: 이 생성자는 데이터를 복사하지 않고 pixels 메모리를 그대로 가리킴
        //       → pixels가 살아 있는 동안만 image를 써야 함 (함수 밖으로 넘길 땐 image.clone())
        cv::Mat image(height, width, CV_8UC1, pixels.data());

        cv::imshow("RAW Image", image);
        cv::waitKey(0);
    }
    catch (const cv::Exception& e) {   // OpenCV 내부 오류 (dll·GUI 문제 등)
        std::cerr << "[OpenCV error] " << e.what() << '\n';
        return 1;
    }
    catch (const std::exception& e) {  // 인자 오류, 파일 오류, 크기 불일치
        std::cerr << "[error] " << e.what() << '\n';
        return 1;
    }
    return 0;
}
