loadfile(lua_dir .. "lib/syntactic_node.lua")();

enum_list = {}

function get_symbol_access_by_type_suffix(identifier, type)
	if(type.type == E_SNT_CONTAINER)then
		if(type.ct == E_CT_VECTOR)then
			return '[i]'
		end
	end
	return ''
end

function get_symbol_access_by_type_prefix(identifier, type, args)
	if(type.type == E_SNT_SIMPLE)then
		return ''
	elseif(type.type == E_SNT_CONTAINER)then
		if(type.ct == E_CT_VECTOR)then
			if(args.arg_list[1].type == E_SNT_SIMPLE)then
				return ''
			else
				return '&'
			end
		elseif(type.ct == E_CT_STRING)then
			return ''
		end
	elseif(type.type == E_SNT_REFER)then
		if(enum_list[type.ot] == nil)then
			return '&'
		else
			return ''
		end
	end
	return ''
end

function get_symbol_access_by_type_prefix_reverse(identifier, type, args)
	if(type.type == E_SNT_SIMPLE)then
		return ''
	elseif(type.type == E_SNT_CONTAINER)then
		if(type.ct == E_CT_VECTOR)then
			if(args.arg_list[1].type == E_SNT_SIMPLE)then
				return ''
			else
				return '*'
			end
		elseif(type.ct == E_CT_STRING)then
			return ''
		end
	elseif(type.type == E_SNT_REFER)then
		if(enum_list[type.ot] == nil)then
			return '*'
		else
			return ''
		end
	end
	return ''
end

function get_symbol_access(identifier, object)
	for k,v in pairs(object.parameters.par_list) do
		if(v.identifier == identifier)then
			prefix = get_symbol_access_by_type_prefix(identifier, v.type, v.args)
			suffix = get_symbol_access_by_type_suffix(identifier, v.type, v.args)
			return prefix .. identifier .. suffix
		end
	end

	for k,v in pairs(object.field_list.field_list)do
		if(v.identifier == identifier)then
			prefix = get_symbol_access_by_type_prefix(identifier, v.type, v.args)
			suffix = get_symbol_access_by_type_suffix(identifier, v.type, v.args)
			return prefix .. 'data->' .. identifier .. suffix
		end
	end

	return identifier
end

function print_line(n, str)
	for i = 1, n do
		io.write('    ')
	end
	print(str)
end

function get_val(val, object)
	if val.type == E_SNVT_IDENTIFIER then
		return get_symbol_access(val.val.identifier, object)
	elseif val.type == E_SNVT_CHAR then
		return val.val.c
	elseif val.type == E_SNVT_DOUBLE then
		return val.val.d
	elseif val.type == E_SNVT_BOOL then
		return val.val.b
	elseif val.type == E_SNVT_STRING then
		return val.val.str
	elseif val.type == E_SNVT_INT64 then
		return val.val.i64
	elseif val.type == E_SNVT_UINT64 then
		return val.val.ui64
	elseif val.type == E_SNVT_HEX_INT64 then
		return val.val.hex_i64
	elseif val.type == E_SNVT_HEX_UINT64 then
		return val.val.hex_ui64
	end
end

function get_type(type, args)
	if(type.type == E_SNT_SIMPLE)then
		if(type.st == E_ST_CHAR)then
			return 'hpchar'
		elseif(type.st == E_ST_DOUBLE)then
			return 'hpdouble'
		elseif(type.st == E_ST_BOOL)then
			return 'hpbool'
		elseif(type.st == E_ST_INT8)then
			return 'hpint8'
		elseif(type.st == E_ST_INT16)then
			return 'hpint16'
		elseif(type.st == E_ST_INT32)then
			return 'hpint32'
		elseif(type.st == E_ST_INT64)then
			return 'hpint64'
		elseif(type.st == E_ST_UINT8)then
			return 'hpuint8'
		elseif(type.st == E_ST_UINT16)then
			return 'hpuint16'
		elseif(type.st == E_ST_UINT32)then
			return 'hpuint32'
		elseif(type.st == E_ST_UINT64)then
			return 'hpuint64'
		end
	elseif(type.type == E_SNT_CONTAINER)then
		if(type.ct == E_CT_VECTOR)then
			return args.arg_list[1].ot
		elseif(type.ct == E_CT_STRING)then
			return 'hpchar'
		end
	elseif(type.type == E_SNT_REFER)then
		return type.ot;
	end
end

