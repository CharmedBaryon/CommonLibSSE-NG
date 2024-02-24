#include "RE/B/BGSKeywordForm.h"

#include "RE/B/BGSKeyword.h"

namespace RE
{
	void BGSKeywordForm::CopyKeywords(const std::vector<RE::BGSKeyword*>& a_copiedData)
	{
		const auto oldData = keywords;

		const auto newSize = a_copiedData.size();
		const auto newData = calloc<BGSKeyword*>(newSize);
		std::ranges::copy(a_copiedData, newData);

		numKeywords = static_cast<std::uint32_t>(newSize);
		keywords = newData;

		free(oldData);
	}

	bool BGSKeywordForm::AddKeyword(BGSKeyword* a_keyword)
	{
		if (!GetKeywordIndex(a_keyword)) {
			std::vector<BGSKeyword*> copiedData{ keywords, keywords + numKeywords };
			copiedData.push_back(a_keyword);
			CopyKeywords(copiedData);
			return true;
		}
		return false;
	}

	bool BGSKeywordForm::AddKeywords(const std::vector<BGSKeyword*>& a_keywords)
	{
		std::vector<BGSKeyword*> copiedData{ keywords, keywords + numKeywords };
		std::ranges::remove_copy_if(a_keywords, std::back_inserter(copiedData), [&](auto& keyword) {
			return std::ranges::find(copiedData, keyword) != copiedData.end();
		});
		CopyKeywords(copiedData);
		return true;
	}

	bool BGSKeywordForm::ContainsKeywordString(std::string_view a_editorID) const
	{
		bool result = false;
		ForEachKeyword([&](const BGSKeyword* a_keyword) {
			if (a_keyword->formEditorID.contains(a_editorID)) {
				result = true;
				return BSContainer::ForEachResult::kStop;
			}
			return BSContainer::ForEachResult::kContinue;
		});
		return result;
	}

	void BGSKeywordForm::ForEachKeyword(std::function<BSContainer::ForEachResult(BGSKeyword*)> a_callback) const
	{
		if (keywords) {
			for (std::uint32_t idx = 0; idx < numKeywords; ++idx) {
				if (keywords[idx] && a_callback(keywords[idx]) == BSContainer::ForEachResult::kStop) {
					return;
				}
			}
		}
	}

	std::optional<BGSKeyword*> BGSKeywordForm::GetKeywordAt(std::uint32_t a_idx) const
	{
		if (a_idx < numKeywords) {
			return std::make_optional(keywords[a_idx]);
		} else {
			return std::nullopt;
		}
	}

	std::optional<std::uint32_t> BGSKeywordForm::GetKeywordIndex(BGSKeyword* a_keyword) const
	{
		if (keywords) {
			for (std::uint32_t i = 0; i < numKeywords; ++i) {
				if (keywords[i] == a_keyword) {
					return i;
				}
			}
		}
		return std::nullopt;
	}

	std::uint32_t BGSKeywordForm::GetNumKeywords() const
	{
		return numKeywords;
	}

	bool BGSKeywordForm::HasKeywordID(FormID a_formID) const
	{
		bool result = false;
		ForEachKeyword([&](const BGSKeyword* a_keyword) {
			if (a_keyword->GetFormID() == a_formID) {
				result = true;
				return BSContainer::ForEachResult::kStop;
			}
			return BSContainer::ForEachResult::kContinue;
		});
		return result;
	}

	bool BGSKeywordForm::HasKeywordString(std::string_view a_editorID) const
	{
		bool result = false;
		ForEachKeyword([&](const BGSKeyword* a_keyword) {
			if (a_keyword->formEditorID == a_editorID) {
				result = true;
				return BSContainer::ForEachResult::kStop;
			}
			return BSContainer::ForEachResult::kContinue;
		});
		return result;
	}

	bool BGSKeywordForm::RemoveKeyword(std::uint32_t a_index)
	{
		std::vector<BGSKeyword*> copiedData{ keywords, keywords + numKeywords };
		copiedData.erase(copiedData.cbegin() + a_index);
		CopyKeywords(copiedData);
		return true;
	}

	bool BGSKeywordForm::RemoveKeyword(BGSKeyword* a_keyword)
	{
		const auto index = GetKeywordIndex(a_keyword);
		return index ? RemoveKeyword(*index) : false;
	}

	bool BGSKeywordForm::RemoveKeywords(const std::vector<BGSKeyword*>& a_keywords)
	{
		std::vector<BGSKeyword*> copiedData{ keywords, keywords + numKeywords };
		if (std::erase_if(copiedData, [&](auto& keyword) { return std::ranges::find(a_keywords, keyword) != a_keywords.end(); }) > 0) {
			CopyKeywords(copiedData);
			return true;
		}
		return false;
	}
}
