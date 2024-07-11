#pragma once

namespace Minecraft {

	struct ShaderSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class Shader
	{
	public:
		Shader(const std::string& filepath);
		Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetInt(const std::string& name, int32_t value);
		void SetInt2(const std::string& name, const glm::ivec2& value);
		void SetInt3(const std::string& name, const glm::ivec3& value);
		void SetInt4(const std::string& name, const glm::ivec4& value);
		void SetIntArray(const std::string& name, int32_t* values, uint32_t count);

		void SetUInt(const std::string& name, uint32_t value);
		void SetUInt2(const std::string& name, const glm::uvec2& value);
		void SetUInt3(const std::string& name, const glm::uvec3& value);
		void SetUInt4(const std::string& name, const glm::uvec4& value);
		void SetUIntArray(const std::string& name, uint32_t* values, uint32_t count);

		void SetFloat(const std::string& name, float value);
		void SetFloat2(const std::string& name, const glm::vec2& value);
		void SetFloat3(const std::string& name, const glm::vec3& value);
		void SetFloat4(const std::string& name, const glm::vec4& value);
		void SetFloatArray(const std::string& name, float* values, uint32_t count);

		void SetMat3(const std::string& name, const glm::mat3& value);
		void SetMat4(const std::string& name, const glm::mat4& value);

		const std::string& GetName() const { return m_Name; }

		void UploadUniformInt(const std::string& name, int32_t value);
		void UploadUniformInt2(const std::string& name, const glm::ivec2& value);
		void UploadUniformInt3(const std::string& name, const glm::ivec3& value);
		void UploadUniformInt4(const std::string& name, const glm::ivec4& value);
		void UploadUniformIntArray(const std::string& name, int32_t* values, uint32_t count);

		void UploadUniformUInt(const std::string& name, uint32_t value);
		void UploadUniformUInt2(const std::string& name, const glm::uvec2& value);
		void UploadUniformUInt3(const std::string& name, const glm::uvec3& value);
		void UploadUniformUInt4(const std::string& name, const glm::uvec4& value);
		void UploadUniformUIntArray(const std::string& name, uint32_t* values, uint32_t count);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
		void UploadUniformFloatArray(const std::string& name, float* values, uint32_t count);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	public:
		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	private:
		ShaderSource PreProcess(const std::string& filepath);

		void CompileShader(const std::string& vertexSource, const std::string& fragmentSource);
	private:
		uint32_t m_RendererID = 0;
		std::string m_Filepath;
		std::string m_Name;
	};

}