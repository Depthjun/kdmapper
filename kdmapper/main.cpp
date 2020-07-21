#include "kdmapper.hpp"

/*
����������
kdmapper 1809,1903,1909
*/

int main(const int argc, char** argv)
{
	std::cout << "kdmapper x64 - 1809 1903 1909" << std::endl;

	//�÷�   kdmapper hack.sys
	if (argc != 2 || std::filesystem::path(argv[1]).extension().string().compare(".sys"))
	{
		std::cout << "[-] ������÷�" << std::endl;
		std::cout << "-> Ҫ��������\t" << argv[0] << " Ҫ���ص�����" << std::endl;
		return -1;
	}

	//�ж�©�������Ƿ�ռ��
	if (intel_driver::IsRunning())
	{
		std::cout << "[-] ©��������ռ��" << std::endl;
		return -1;
	}

	//�ж�׼�����صĺڿ������Ƿ����
	const std::string driver_path = argv[1];
	if (!std::filesystem::exists(driver_path))
	{
		std::cout << "[-] �����ļ� " << driver_path << " ������" << std::endl;
		return -1;
	}

	//��ȡ©������������
	HANDLE iqvw64e_device_handle = intel_driver::Load();
	if (!iqvw64e_device_handle || iqvw64e_device_handle == INVALID_HANDLE_VALUE)
	{
		std::cout << "[-] �޷�����©������ iqvw64e.sys" << std::endl;
		return -1;
	}

	//����©������ӳ��ڿ�����
	if (!kdmapper::MapDriver(iqvw64e_device_handle, driver_path))
	{
		std::cout << "[-] �޷�ӳ��ڿ����� " << driver_path << std::endl;
		intel_driver::Unload(iqvw64e_device_handle);
		return -1;
	}

	//ж��©������
	intel_driver::Unload(iqvw64e_device_handle);

	std::cout << "[+] �������سɹ�" << std::endl;
}