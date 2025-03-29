package org.raymyers.ayg;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.datatype.jdk8.Jdk8Module;
import com.spun.util.ObjectUtils;
import org.approvaltests.Approvals;
import org.approvaltests.core.Options;

public class ApprovalHelpers {
    public static void verifyAsJson(Object o) {
        verifyAsJson(o, new Options());
    }

    public static void verifyAsJson(Object o, Options options) {
        Approvals.verify(asJson(o), options.forFile().withExtension(".json"));
    }

    public static String asJson(Object o) {
        try {
            ObjectMapper objectMapper = new ObjectMapper();
            objectMapper.registerModule(new Jdk8Module());
            return objectMapper.writerWithDefaultPrettyPrinter().writeValueAsString(o);
        } catch (JsonProcessingException e) {
            throw ObjectUtils.throwAsError(e);
        }
    }
}