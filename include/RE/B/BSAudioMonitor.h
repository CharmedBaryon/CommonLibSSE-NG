#pragma once

namespace RE
{
	namespace BSAudioMonitor
	{
		class Request
		{
		public:
			Request(std::uint16_t a_monitor, std::uint16_t a_sendLevel) :
				monitor(a_monitor),
				sendLevel(a_sendLevel)
			{}

			[[nodiscard]] std::uint32_t QID() const { return monitor; }
			[[nodiscard]] std::uint16_t QSendLevel() const { return sendLevel; }

			// members
			std::uint16_t monitor;    // 0
			std::uint16_t sendLevel;  // 2
		};
		static_assert(sizeof(Request) == 0x4);

		class Receiver
		{
		public:
			Receiver(const float& a_amplitude) :
				amplitude(std::addressof(a_amplitude))
			{}

			[[nodiscard]] float QAmplitude() const { return *amplitude; }

			// members
			const float* amplitude;  // 0
		};
		static_assert(sizeof(Receiver) == 0x8);
		static_assert(!REL::detail::is_x64_pod_v<Receiver>);
	}
}
